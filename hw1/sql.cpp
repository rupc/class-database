#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <iostream>
#include <sstream>
void display_row();
void display_header();

MYSQL_ROW sqlrow;
MYSQL *con;
MYSQL_RES *res_ptr;

const char *host = "192.168.0.5";
const char *userid = "astral";
const char *passwd = "nau384";
const char *db_name = "test";

int main(int argc, char **argv) {  
    con = mysql_init(nullptr);
    int first_row = 1;
    if (con == nullptr) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    
    mysql_options(con, MYSQL_SET_CHARSET_NAME, "utf8");
    con = mysql_real_connect(con, host, userid, passwd, db_name, 0, nullptr, 0);
    printf("%s\n", mysql_get_client_info());
    printf("%s\n", mysql_get_host_info(con));
    printf("%s\n", mysql_get_server_info(con));
    // check connection

    if (con) {
        printf("Connection success\n");
    } else {
        fprintf(stderr, "Connection error %d: %s\n", mysql_errno(con), mysql_error(con));
        exit(-1);
    }  
    std::string query;
    while (true) {
        std::cout << "Enter the query : ";
        std::getline(std::cin, query);
        if (query == "quit") {
            std::cout << "End the program" << "\n";
            break;
        }

        int res = mysql_query(con, query.c_str());
        if (res) {
            std::cout << mysql_error(con) << "\n";
            continue;
        }
        // ignore() needed if ">>" used
        std::istringstream iss(query);
        std::string cmd;
        iss >> cmd;
        //std::cout << cmd << "\n";
        if (cmd == "select") {
            // select
            res_ptr = mysql_store_result(con);
            std::cout << "Retrieved " << mysql_num_rows(res_ptr) << "\n";

            while ((sqlrow = mysql_fetch_row(res_ptr))) {
                if (first_row) {
                    display_header();
                    first_row = 0;
                }
                display_row();
            }

            if (mysql_errno(con)) {
                std::cerr << "Retrive error: " << mysql_error(con) << std::endl;
            }
            mysql_free_result(res_ptr);
        } else if (cmd == "insert") {
            // update, delete, insert
            int affcted_rows = mysql_affected_rows(con);
            std::cout << "Inserted " << (unsigned long)affcted_rows << "\n";
        } else if (cmd == "use") {
            std::string new_db_name;
            iss >> new_db_name;
            int res = mysql_select_db(con, new_db_name.c_str());
            if (res == 0) {
                std::cout << "Database changed to " << new_db_name << "\n";
            } else {
                std::cout << "Dabased change Fail!" << "\n";
            }
        }

        std::cout << "Your query : " << query << "\n";
    }
    mysql_close(con);

    return EXIT_SUCCESS;
}

void display_header() {
    MYSQL_FIELD *field_ptr;
    printf("Column details\n");
    while ((field_ptr = mysql_fetch_field(res_ptr)) != nullptr) {
        printf("\t Name: %s\n", field_ptr->name);
        printf("\t Type: ");
        
        if (IS_NUM(field_ptr->type)) {
            printf("Numeric field\n");
        } else {
            switch (field_ptr->type) {
                case FIELD_TYPE_VAR_STRING:
                    printf("VARCHAR\n");
                    break;
                case FIELD_TYPE_LONG:
                    printf("LONG\n");
                    break;
                case FIELD_TYPE_STRING:
                    printf("STRING\n");
                    break;
                default:
                    printf("Type is %d, check in mysql_com.h\n", field_ptr->type);
            }
        }

        printf("\t Max width %ld\n", field_ptr->length);
        if (field_ptr->flags &AUTO_INCREMENT_FLAG)
            printf("\t Auto increment\n");
        printf("\n");
    }
}
void display_row() {
    unsigned field_count = 0;
    while (field_count < mysql_field_count(con)) {
        printf("%s ", sqlrow[field_count++]);
    }
    printf("\n");
}
