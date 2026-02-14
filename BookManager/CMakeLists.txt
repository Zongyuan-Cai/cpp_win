cmake_minimum_required(VERSION 3.10)
project(BookManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/utf-8)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

add_executable(BookManager
    src/main.cpp
    src/Book.cpp
    src/FileManager.cpp
    src/Library.cpp
)

target_include_directories(BookManager PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/single_include
)
