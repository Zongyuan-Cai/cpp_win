#include "Library.h"
#include <iostream>
#include <algorithm>

Library::Library() : dataPath_("books.txt") {}

void Library::addBook(std::unique_ptr<Book> book) {
    if (book) {
        books_.push_back(std::move(book));
        std::cout << "添加成功\n";
    }
}

void Library::removeBook(int id) {
    auto it = std::find_if(books_.begin(), books_.end(),
        [id](const std::unique_ptr<Book>& b) { return b->getId() == id; });
    if (it != books_.end()) {
        books_.erase(it);
        std::cout << "删除成功\n";
    } else {
        std::cout << "未找到该图书\n";
    }
}

Book* Library::findBook(int id) {
    auto it = std::find_if(books_.begin(), books_.end(),
        [id](const std::unique_ptr<Book>& b) { return b->getId() == id; });
    return it != books_.end() ? it->get() : nullptr;
}

Book* Library::findBookByTitle(const std::string& title) {
    auto it = std::find_if(books_.begin(), books_.end(),
        [&title](const std::unique_ptr<Book>& b) { return b->getTitle() == title; });
    return it != books_.end() ? it->get() : nullptr;
}

void Library::listAllBooks() const {
    if (books_.empty()) {
        std::cout << "暂无图书\n";
        return;
    }
    for (const auto& b : books_) {
        b->display();  // 多态调用
    }
}

void Library::listBooksByType(const std::string& type) const {
    bool found = false;
    for (const auto& b : books_) {
        if (b->getType() == type) {
            b->display();
            found = true;
        }
    }
    if (!found) std::cout << "未找到该类型图书\n";
}

void Library::borrowBook(int id) {
    Book* b = findBook(id);
    if (b) {
        if (b->isBorrowed())
            std::cout << "该书已借出\n";
        else {
            b->setBorrowed(true);
            std::cout << "借阅成功\n";
        }
    } else {
        std::cout << "未找到该图书\n";
    }
}

void Library::returnBook(int id) {
    Book* b = findBook(id);
    if (b) {
        b->setBorrowed(false);
        std::cout << "归还成功\n";
    } else {
        std::cout << "未找到该图书\n";
    }
}

// RAII 文件加载
bool Library::loadFromFile(const std::string& path) {
    FileReader reader(path);  // RAII: 析构时自动关闭
    if (!reader.isOpen()) return false;

    books_.clear();
    std::string line;
    while (!reader.eof()) {
        line = reader.readLine();
        if (line.empty()) continue;

        size_t sep = line.find('|');
        if (sep == std::string::npos) continue;
        std::string type = line.substr(0, sep);
        std::string data = line.substr(sep + 1);

        auto book = createBookFromLine(type, data);
        if (book) books_.push_back(std::move(book));
    }
    return true;
}

// RAII 文件保存
bool Library::saveToFile(const std::string& path) const {
    FileWriter writer(path);  // RAII: 析构时自动刷新并关闭
    if (!writer.isOpen()) return false;

    for (const auto& b : books_) {
        writer.stream() << b->toFileString() << '\n';  // 多态序列化
    }
    return true;
}

std::unique_ptr<Book> Library::createBookFromLine(const std::string& type,
                                                   const std::string& data) {
    if (type == "FICTION") {
        auto p = std::make_unique<FictionBook>("", "", 0);
        p->fromFileString(data);
        return p;
    }
    if (type == "TECHNICAL") {
        auto p = std::make_unique<TechnicalBook>("", "", 0);
        p->fromFileString(data);
        return p;
    }
    if (type == "REFERENCE") {
        auto p = std::make_unique<ReferenceBook>("", "", 0, false);
        p->fromFileString(data);
        return p;
    }
    return nullptr;
}
