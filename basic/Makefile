

TARGET=sql
INCLUDE=/usr/include/mariadb
LIBDIR=/usr/lib/mariadb
LIB=mysqlclient
CXX=g++
CXXFLAGS= -std=c++14 -O2

OBJ=sql.o
SRC=$(OBJ:.o=.cpp)

$(TARGET): sql.o
	$(CXX) -o $(TARGET) $(OBJ) -L$(LIBDIR) -l$(LIB)
	chmod +x $(TARGET)

sql.o: sql.cpp
	$(CXX) -c $(SRC) $(CXXFLAGS)

run:
	./$(TARGET)

clean:
	rm *.o
	rm $(TARGET)


