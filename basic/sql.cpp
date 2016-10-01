

#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <iostream>
void display_row();
void display_header();

MYSQL_ROW sqlrow;
MYSQL *con;
MYSQL_RES *res_ptr;
int main(int argc, char **argv) {  
  con = mysql_init(nullptr);
  int first_row = 1;

  if (con == nullptr) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }
  mysql_options(con, MYSQL_SET_CHARSET_NAME, "utf8");
  con = mysql_real_connect(con, "192.168.0.5", "astral", "nau384", "iden", 0, nullptr, 0);
  printf("%s\n", mysql_get_client_info());
  printf("%s\n", mysql_get_host_info(con));
  printf("%s\n", mysql_get_server_info(con));
  // check connection
  if (con) {
      printf("Connection success\n");
      const char *query = "select * from idpass order by number";
      int res = mysql_query(con, query);
      if (res) {
          std::cout << "select error: " << mysql_error(con) << "\n";
      } else {
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
      }
      mysql_close(con);

      
  } else {
      fprintf(stderr, "Connection error %d: %s\n",
              mysql_errno(con), mysql_error(con));
  }  

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
        printf("%s\n", sqlrow[field_count++]);
    }
    printf("\n");
}
