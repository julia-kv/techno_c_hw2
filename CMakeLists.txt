cmake_minimum_required(VERSION 3.16.3)
project(C___HW2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

option(IS_STATIC "static_library" ON)

set(LIB_SOURCE_FILES structs.c create_db.c find.c structs.h find.h create_database.h)
add_library(db_lib STATIC ${LIB_SOURCE_FILES})

set(LIB_SOURCE_FILES structs.c create_db_dynamic.c find.c structs.h find.h create_database.h)
add_library(db_lib_dynamic SHARED ${LIB_SOURCE_FILES})

add_executable(main main.c)
if(IS_STATIC)
    target_link_libraries(main db_lib)
else()
    target_link_libraries(main db_lib_dynamic)
endif()

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_db test.cpp)
target_link_libraries(test_db ${GTEST_LIBRARIES} pthread db_lib)