enable_testing()

cmake_minimum_required(VERSION 2.8)
project(STMBProject)

set(ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${ROOT}")
set(GTEST_DIR "${SRC_DIR}/tests/")

list(APPEND DIRS
    "${ROOT}"
    "${SRC_DIR}"
    "${SRC_DIR}/Handler"
    "${SRC_DIR}/Event"
    "${SRC_DIR}/Model"
    "${SRC_DIR}/Dao"
    "${GMOCK_TESTS_SOURCE}/include/gtest"
    "${GMOCK_TESTS_SOURCE}/include/gmock"
    "${GMOCK_TESTS_SOURCE}/lib"
)

include_directories(${DIRS})
add_executable(main main.cpp)
add_definitions(-std=gnu++11 -Wall)
target_link_libraries(main pqxx pq pthread)

add_executable(unittest ${GTEST_DIR}/unittest.cpp)
add_executable(integrationtest ${GTEST_DIR}/integrationtest.cpp)
include_directories(${GTEST_DIR}/include)

target_link_libraries(integrationtest ${GTEST_DIR}/lib/libgtest.so)
target_link_libraries(integrationtest ${GTEST_DIR}/lib/libgtest_main.so)
target_link_libraries(integrationtest ${GTEST_DIR}/lib/libgmock.so)
target_link_libraries(integrationtest ${GTEST_DIR}/lib/libgmock_main.so)
target_link_libraries(integrationtest pthread )

target_link_libraries(unittest ${GTEST_DIR}/lib/libgtest.so)
target_link_libraries(unittest ${GTEST_DIR}/lib/libgtest_main.so)
target_link_libraries(unittest ${GTEST_DIR}/lib/libgmock.so)
target_link_libraries(unittest ${GTEST_DIR}/lib/libgmock_main.so)
target_link_libraries(unittest pthread )


enable_testing()


add_test(

    NAME unittest
    COMMAND unittest
)

add_test(

    NAME integrationtest
    COMMAND integrationtest
)



