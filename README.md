# Mini Bank Project
A C++ Event Database Program

## Getting Started


### Prerequesites
* libpqxx - To Production database
* Postgresql

## Building The Project

With Cmake

    * mkdir build
    * cd build
    * cmake ../


With GCC

    * g++ main.cpp -o main -std=c++11 -lpqxx -lpq
    * g++ -L./lib -lgtest -lgtest_main -lgmock -lgmock_main -pthread -lpthread (testfile.cpp) -o test

## Running The Testes

    After compile the tests, just open the test and wait for completion

## Author

* **Thiago Giecht**

