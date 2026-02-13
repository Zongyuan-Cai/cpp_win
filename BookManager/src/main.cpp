#include "Library.h"
#include "Book.h"s
#include <iostream>
#include <string>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMenu() {
    std::cout << "\n======== 图书管理系统 ========\n"
              << "1. 添加图书\n"
              << "2. 删除图书\n"
              << "3. 查询图书\n"
              << "4. 列出全部\n"
              << "5. 按类型列出\n"
              << "6. 借阅\n"
              << "7. 归还\n"
              << "8. 保存到文件\n"
              << "9. 从文件加载\n"
              << "0. 退出\n"
              << "==============================\n";
}

int main() {
    Library lib;  // RAII: 析构时自动释放所有 unique_ptr<Book>
    const std::string dataPath = "books.json";

    // 启动时自动加载
    if (lib.loadFromFile(dataPath)) {
        std::cout << "已从 " << dataPath << " 加载数据\n";
    }

    int choice;
    while (true) {
        showMenu();
        std::cout << "请选择: ";
        if (!(std::cin >> choice)) {
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                int type;
                std::string title, author, extra;
                int year;
                std::cout << "类型: 1-文学 2-技术 3-参考\n选择: ";
                std::cin >> type;
                clearInput();
                std::cout << "书名: "; std::getline(std::cin, title);
                std::cout << "作者: "; std::getline(std::cin, author);
                std::cout << "年份: "; std::cin >> year;
                clearInput();

                if (type == 1) {
                    std::cout << "文学类型(如: 小说): "; std::getline(std::cin, extra);
                    lib.addBook(std::make_unique<FictionBook>(title, author, year, extra));
                } else if (type == 2) {
                    std::cout << "技术领域(如: C++): "; std::getline(std::cin, extra);
                    lib.addBook(std::make_unique<TechnicalBook>(title, author, year, extra));
                } else if (type == 3) {
                    int enc;
                    std::cout << "是否百科全书(1/0): "; std::cin >> enc;
                    lib.addBook(std::make_unique<ReferenceBook>(title, author, year, enc == 1));
                } else {
                    std::cout << "无效类型\n";
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "输入图书ID: "; std::cin >> id;
                lib.removeBook(id);
                break;
            }
            case 3: {
                std::string key;
                std::cout << "输入书名或ID: "; clearInput(); std::getline(std::cin, key);
                if (key.empty()) break;
                if (isdigit(key[0])) {
                    Book* b = lib.findBook(std::stoi(key));
                    if (b) b->display();
                    else std::cout << "未找到\n";
                } else {
                    Book* b = lib.findBookByTitle(key);
                    if (b) b->display();
                    else std::cout << "未找到\n";
                }
                break;
            }
            case 4:
                lib.listAllBooks();
                break;
            case 5: {
                std::string t;
                std::cout << "类型(文学/技术/参考): "; clearInput(); std::getline(std::cin, t);
                lib.listBooksByType(t);
                break;
            }
            case 6: {
                int id;
                std::cout << "输入图书ID: "; std::cin >> id;
                lib.borrowBook(id);
                break;
            }
            case 7: {
                int id;
                std::cout << "输入图书ID: "; std::cin >> id;
                lib.returnBook(id);
                break;
            }
            case 8:
                if (lib.saveToFile(dataPath))
                    std::cout << "保存成功\n";
                else
                    std::cout << "保存失败\n";
                break;
            case 9:
                if (lib.loadFromFile(dataPath))
                    std::cout << "加载成功，共 " << lib.size() << " 本\n";
                else
                    std::cout << "加载失败或文件为空\n";
                break;
            case 0:
                lib.saveToFile(dataPath);  // 退出前自动保存
                std::cout << "再见!\n";
                return 0;
            default:
                std::cout << "无效选择\n";
        }
    }
}
