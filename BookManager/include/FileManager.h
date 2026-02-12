#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <memory>
#include <vector>

class Book;  // 前向声明

// RAII 文件管理器 - 构造时获取资源，析构时自动释放
class FileManager {
public:
    explicit FileManager(const std::string& path);
    ~FileManager();

    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    bool isOpen() const { return file_.is_open(); }
    bool good() const { return file_.good(); }
    std::fstream& stream() { return file_; }
    const std::string& path() const { return path_; }

private:
    std::string path_;
    std::fstream file_;
};

// RAII 读取器 - 专门用于读取，析构时关闭
class FileReader {
public:
    explicit FileReader(const std::string& path);
    ~FileReader();

    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;

    bool isOpen() const { return file_.is_open(); }
    std::ifstream& stream() { return file_; }
    std::string readLine();
    bool eof() const { return file_.eof(); }

private:
    std::string path_;
    std::ifstream file_;
};

// RAII 写入器 - 专门用于写入，析构时关闭并刷新
class FileWriter {
public:
    explicit FileWriter(const std::string& path);
    ~FileWriter();

    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    bool isOpen() const { return file_.is_open(); }
    std::ofstream& stream() { return file_; }

private:
    std::string path_;
    std::ofstream file_;
};

#endif // FILE_MANAGER_H
