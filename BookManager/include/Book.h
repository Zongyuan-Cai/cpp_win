#ifndef BOOK_H
#define BOOK_H

#include <memory>
#include <string>
#include <ostream>

// 抽象基类 - 多态设计
class Book {
public:
    Book(const std::string& title, const std::string& author, int year);
    virtual ~Book() = default;

    virtual std::string getType() const = 0;        // 纯虚函数
    virtual void display() const;                    // 可被派生类重写
    virtual std::string toFileString() const;        // 序列化，多态
    virtual void fromFileString(const std::string&); // 反序列化，多态

    const std::string& getTitle() const { return title_; }
    const std::string& getAuthor() const { return author_; }
    int getYear() const { return year_; }
    int getId() const { return id_; }
    bool isBorrowed() const { return borrowed_; }
    void setBorrowed(bool b) { borrowed_ = b; }

protected:
    int id_;
    std::string title_;
    std::string author_;
    int year_;
    bool borrowed_;
    static int nextId_;
};

// 文学类图书
class FictionBook : public Book {
public:
    FictionBook(const std::string& title, const std::string& author, int year,
                const std::string& genre = "未分类");
    std::string getType() const override { return "文学"; }
    void display() const override;
    std::string toFileString() const override;
    void fromFileString(const std::string& s) override;
    const std::string& getGenre() const { return genre_; }

private:
    std::string genre_;
};

// 技术类图书
class TechnicalBook : public Book {
public:
    TechnicalBook(const std::string& title, const std::string& author, int year,
                  const std::string& field = "未分类");
    std::string getType() const override { return "技术"; }
    void display() const override;
    std::string toFileString() const override;
    void fromFileString(const std::string& s) override;
    const std::string& getField() const { return field_; }

private:
    std::string field_;
};

// 参考工具书
class ReferenceBook : public Book {
public:
    ReferenceBook(const std::string& title, const std::string& author, int year,
                  bool encyclopedia = false);
    std::string getType() const override { return "参考"; }
    void display() const override;
    std::string toFileString() const override;
    void fromFileString(const std::string& s) override;
    bool isEncyclopedia() const { return encyclopedia_; }

private:
    bool encyclopedia_;
};

#endif // BOOK_H
