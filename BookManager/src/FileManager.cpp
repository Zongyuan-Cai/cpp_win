#include "FileManager.h"
#include <iostream>

// RAII: 构造时打开文件
FileManager::FileManager(const std::string& path) : path_(path) {
    file_.open(path, std::ios::in | std::ios::out | std::ios::app);
    if (!file_.is_open()) {
        file_.clear();
        file_.open(path, std::ios::out);  // 创建新文件
    }
}

// RAII: 析构时自动关闭文件
FileManager::~FileManager() {
    if (file_.is_open()) {
        file_.close();
    }
}

// RAII 读取器
FileReader::FileReader(const std::string& path) : path_(path) {
    file_.open(path);
}

FileReader::~FileReader() {
    if (file_.is_open()) {
        file_.close();
    }
}

std::string FileReader::readLine() {
    std::string line;
    if (file_.is_open() && std::getline(file_, line)) {
        return line;
    }
    return "";
}

// RAII 写入器 - 析构时关闭并刷新缓冲区
FileWriter::FileWriter(const std::string& path) : path_(path) {
    file_.open(path);
}

FileWriter::~FileWriter() {
    if (file_.is_open()) {
        file_.flush();
        file_.close();
    }
}
