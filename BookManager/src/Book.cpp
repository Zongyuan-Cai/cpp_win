#include "Book.h"
#include <sstream>
#include <iostream>
#include <algorithm>

int Book::nextId_ = 1;

Book::Book(const std::string& title, const std::string& author, int year)
    : id_(nextId_++), title_(title), author_(author), year_(year), borrowed_(false) {}

void Book::display() const {
    std::cout << "[ID:" << id_ << "] " << title_ << " | " << author_
              << " | " << year_ << " | " << (borrowed_ ? "已借出" : "可借") << '\n';
}

std::string Book::toFileString() const {
    std::ostringstream oss;
    oss << id_ << '|' << title_ << '|' << author_ << '|' << year_ << '|' << (borrowed_ ? 1 : 0);
    return oss.str();
}

void Book::fromFileString(const std::string& s) {
    std::istringstream iss(s);
    std::string part;
    std::getline(iss, part, '|'); id_ = std::stoi(part);
    std::getline(iss, title_, '|');
    std::getline(iss, author_, '|');
    std::getline(iss, part, '|'); year_ = std::stoi(part);
    std::getline(iss, part, '|'); borrowed_ = (part == "1");
    if (id_ >= nextId_) nextId_ = id_ + 1;
}

void Book::fromJson(const nlohmann::json& j) {
    if (j.contains("id")) id_ = j["id"].get<int>();
    if (j.contains("title")) title_ = j["title"].get<std::string>();
    if (j.contains("author")) author_ = j["author"].get<std::string>();
    if (j.contains("year")) year_ = j["year"].get<int>();
    if (j.contains("borrowed")) borrowed_ = j["borrowed"].get<bool>();
    if (id_ >= nextId_) nextId_ = id_ + 1;
}

// --- FictionBook ---
FictionBook::FictionBook(const std::string& title, const std::string& author,
                         int year, const std::string& genre)
    : Book(title, author, year), genre_(genre) {}

void FictionBook::display() const {
    std::cout << "[文学] [ID:" << id_ << "] " << title_ << " | " << author_
              << " | " << year_ << " | 类型:" << genre_
              << " | " << (borrowed_ ? "已借出" : "可借") << '\n';
}

std::string FictionBook::toFileString() const {
    return "FICTION|" + Book::toFileString() + "|" + genre_;
}

void FictionBook::fromFileString(const std::string& s) {
    size_t last = s.rfind('|');
    if (last == std::string::npos) return;
    genre_ = s.substr(last + 1);
    Book::fromFileString(s.substr(0, last));
}

nlohmann::json FictionBook::toJson() const {
    nlohmann::json j = nlohmann::json::object();
    j["type"] = "FICTION";
    j["id"] = id_;
    j["title"] = title_;
    j["author"] = author_;
    j["year"] = year_;
    j["borrowed"] = borrowed_;
    j["genre"] = genre_;
    return j;
}

void FictionBook::fromJson(const nlohmann::json& j) {
    Book::fromJson(j);
    if (j.contains("genre")) genre_ = j["genre"].get<std::string>();
}

// --- TechnicalBook ---
TechnicalBook::TechnicalBook(const std::string& title, const std::string& author,
                             int year, const std::string& field)
    : Book(title, author, year), field_(field) {}

void TechnicalBook::display() const {
    std::cout << "[技术] [ID:" << id_ << "] " << title_ << " | " << author_
              << " | " << year_ << " | 领域:" << field_
              << " | " << (borrowed_ ? "已借出" : "可借") << '\n';
}

std::string TechnicalBook::toFileString() const {
    return "TECHNICAL|" + Book::toFileString() + "|" + field_;
}

void TechnicalBook::fromFileString(const std::string& s) {
    size_t last = s.rfind('|');
    if (last == std::string::npos) return;
    field_ = s.substr(last + 1);
    Book::fromFileString(s.substr(0, last));
}

nlohmann::json TechnicalBook::toJson() const {
    nlohmann::json j = nlohmann::json::object();
    j["type"] = "TECHNICAL";
    j["id"] = id_;
    j["title"] = title_;
    j["author"] = author_;
    j["year"] = year_;
    j["borrowed"] = borrowed_;
    j["field"] = field_;
    return j;
}

void TechnicalBook::fromJson(const nlohmann::json& j) {
    Book::fromJson(j);
    if (j.contains("field")) field_ = j["field"].get<std::string>();
}

// --- ReferenceBook ---
ReferenceBook::ReferenceBook(const std::string& title, const std::string& author,
                             int year, bool encyclopedia)
    : Book(title, author, year), encyclopedia_(encyclopedia) {}

void ReferenceBook::display() const {
    std::cout << "[参考] [ID:" << id_ << "] " << title_ << " | " << author_
              << " | " << year_ << " | " << (encyclopedia_ ? "百科全书" : "工具书")
              << " | " << (borrowed_ ? "已借出" : "可借") << '\n';
}

std::string ReferenceBook::toFileString() const {
    return "REFERENCE|" + Book::toFileString() + "|" + (encyclopedia_ ? "1" : "0");
}

void ReferenceBook::fromFileString(const std::string& s) {
    size_t last = s.rfind('|');
    if (last == std::string::npos) return;
    encyclopedia_ = (s.substr(last + 1) == "1");
    Book::fromFileString(s.substr(0, last));
}

nlohmann::json ReferenceBook::toJson() const {
    nlohmann::json j = nlohmann::json::object();
    j["type"] = "REFERENCE";
    j["id"] = id_;
    j["title"] = title_;
    j["author"] = author_;
    j["year"] = year_;
    j["borrowed"] = borrowed_;
    j["encyclopedia"] = encyclopedia_;
    return j;
}

void ReferenceBook::fromJson(const nlohmann::json& j) {
    Book::fromJson(j);
    if (j.contains("encyclopedia")) encyclopedia_ = j["encyclopedia"].get<bool>();
}
