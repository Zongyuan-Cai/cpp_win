cmake_minimum_required(VERSION 3.10)

# 指定使用 g++ 编译（Windows 下需先安装 MinGW/MSYS2 并加入 PATH）
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(BookManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 源文件 UTF-8，避免中文等字符报错
if(MSVC)
    add_compile_options(/utf-8)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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
)
