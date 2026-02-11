cmake_minimum_required(VERSION 3.10)
project(StudentManager CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/core/Student.cpp
    src/core/StudentManager.cpp
    src/core/Menu.cpp
    src/storage/FileManager.cpp
    src/utils/Utils.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# 数据目录（运行时从可执行文件所在目录相对查找 data/）
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
