cmake_minimum_required(VERSION 3.16)

project(scalc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
        -lpthread\
        -static-libgcc \
        -static-libstdc++\
")

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/expression
        ${PROJECT_SOURCE_DIR}/include/filemanager
        ${PROJECT_SOURCE_DIR}/util/filemanager
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/app
        ${PROJECT_SOURCE_DIR}/tests)

add_library(eval_library STATIC
        src/filemanager.cpp
        src/util.cpp
        src/expression.cpp
        include/filemanager/filemanager.hpp
        include/util/util.hpp
        include/expression/expression.hpp
        )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(scalc
        app/scalc.cpp)

target_link_libraries(scalc eval_library pthread)

add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(tests tests/basictest.cpp)
file(COPY tests/files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(tests gtest gtest_main eval_library)
