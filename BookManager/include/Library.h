#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "FileManager.h"
#include <vector>
#include <memory>
#include <string>

class Library {
public:
    Library();
    ~Library() = default;

    void addBook(std::unique_ptr<Book> book);
    void removeBook(int id);
    Book* findBook(int id);
    Book* findBookByTitle(const std::string& title);
    void listAllBooks() const;
    void listBooksByType(const std::string& type) const;
    void borrowBook(int id);
    void returnBook(int id);

    // 文件读写 - 使用 RAII
    bool loadFromFile(const std::string& path);
    bool saveToFile(const std::string& path) const;

    size_t size() const { return books_.size(); }

private:
    std::vector<std::unique_ptr<Book>> books_;  // RAII: unique_ptr 管理动态内存
    std::string dataPath_;

    std::unique_ptr<Book> createBookFromLine(const std::string& type,
                                             const std::string& data);
};

#endif // LIBRARY_H
