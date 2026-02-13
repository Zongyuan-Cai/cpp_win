cmake_minimum_required(VERSION 3.10)
project(BookManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 若要用 g++ 编译，配置时加: -DCMAKE_CXX_COMPILER=g++ -G "MinGW Makefiles"
# 不指定则使用系统默认（如 Visual Studio 的 MSVC）

# 源文件 UTF-8，避免中文等字符报错
if(MSVC)
    add_compile_options(/utf-8)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# nlohmann/json（仅头文件，v3.11.2 发布包为 json.tar.xz 不是 json.tar.gz）
cmake_policy(SET CMP0135 NEW)  # 消除 DOWNLOAD_EXTRACT_TIMESTAMP 警告
include(FetchContent)
FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

add_executable(BookManager
    src/main.cpp
    src/Book.cpp
    src/FileManager.cpp
    src/Library.cpp
)

target_include_directories(BookManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(BookManager PRIVATE nlohmann_json::nlohmann_json)
