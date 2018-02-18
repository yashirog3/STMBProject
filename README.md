# Mini Bank Project
A C++ Event Database Program

### Prerequesites

To Production database

* libpqxx 
* Postgresql

##Getting Started



## Building The Project

With Cmake

    * mkdir build
    * cd build
    * cmake ../

If you-re using linux, there's a generated makefile on build directory. Just cd and make


With GCC

    * g++ main.cpp -o main -std=c++11 -lpqxx -lpq
    * g++ -L./lib -lgtest -lgtest_main -lgmock -lgmock_main -pthread -lpthread (testfile.cpp) -o test

## Running The Testes

After Make Files
      
-    make tests

## Author

* **Thiago Giecht**

