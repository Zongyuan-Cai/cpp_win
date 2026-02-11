#include "core/Menu.h"
#include "utils/Utils.h"
#include <iostream>
#include <limits>

namespace student_manager {

Menu::Menu(const std::string& dataPath) : dataPath_(dataPath) {
    manager_ = std::make_unique<StudentManager>();
}

void Menu::run() {
    loadFromFile();
    while (true) {
        showMainMenu();
        int choice = utils::readInt("请选择");
        switch (choice) {
            case 1: addStudent(); break;
            case 2: removeStudent(); break;
            case 3: findStudent(); break;
            case 4: updateStudent(); break;
            case 5: listStudents(); break;
            case 6: saveToFile(); break;
            case 0:
                saveToFile();
                std::cout << "再见！\n";
                return;
            default:
                std::cout << "无效选项，请重试。\n";
        }
    }
}

void Menu::showMainMenu() {
    std::cout << "\n========== 学生管理系统 ==========\n"
              << "  1. 添加学生\n"
              << "  2. 删除学生\n"
              << "  3. 查询学生\n"
              << "  4. 修改学生\n"
              << "  5. 显示全部\n"
              << "  6. 保存到文件\n"
              << "  0. 退出\n"
              << "================================\n";
}

void Menu::printStudent(const Student& s) const {
    std::cout << "  学号: " << s.id << "  姓名: " << s.name
              << "  专业: " << s.major << "  年龄: " << s.age
              << "  成绩: " << s.score << '\n';
}

void Menu::addStudent() {
    std::uint32_t id = static_cast<std::uint32_t>(utils::readUInt("学号"));
    std::string name = utils::readLine("姓名");
    std::string major = utils::readLine("专业");
    int age = utils::readInt("年龄");
    double score = utils::readDouble("成绩");
    Student s(id, name, major, age, score);
    if (manager_->add(s)) {
        std::cout << "添加成功。\n";
    } else {
        std::cout << "添加失败：学号已存在。\n";
    }
}

void Menu::removeStudent() {
    std::uint32_t id = static_cast<std::uint32_t>(utils::readUInt("要删除的学号"));
    if (manager_->remove(id)) {
        std::cout << "删除成功。\n";
    } else {
        std::cout << "未找到该学号。\n";
    }
}

void Menu::findStudent() {
    std::uint32_t id = static_cast<std::uint32_t>(utils::readUInt("学号"));
    auto opt = manager_->find(id);
    if (opt) {
        std::cout << "查询结果：\n";
        printStudent(*opt);
    } else {
        std::cout << "未找到该学生。\n";
    }
}

void Menu::updateStudent() {
    std::uint32_t id = static_cast<std::uint32_t>(utils::readUInt("要修改的学号"));
    auto opt = manager_->find(id);
    if (!opt) {
        std::cout << "未找到该学生。\n";
        return;
    }
    std::string name = utils::readLine("姓名（直接回车保留: " + opt->name + ")");
    if (name.empty()) name = opt->name;
    std::string major = utils::readLine("专业（直接回车保留: " + opt->major + ")");
    if (major.empty()) major = opt->major;
    int age = utils::readIntDefault("年龄（直接回车保留: " + std::to_string(opt->age) + ")", opt->age);
    double score = utils::readDoubleDefault("成绩（直接回车保留: " + std::to_string(opt->score) + ")", opt->score);
    Student s(id, name, major, age, score);
    manager_->update(id, s);
    std::cout << "修改成功。\n";
}

void Menu::listStudents() {
    const auto& all = manager_->getAll();
    if (all.empty()) {
        std::cout << "暂无学生记录。\n";
        return;
    }
    std::cout << "共 " << all.size() << " 条记录：\n";
    for (const auto& s : all) {
        printStudent(s);
    }
}

void Menu::loadFromFile() {
    storage::FileManager fm(dataPath_);
    if (fm.load(*manager_)) {
        std::cout << "已从文件加载 " << manager_->getAll().size() << " 条记录。\n";
    }
}

void Menu::saveToFile() {
    storage::FileManager fm(dataPath_);
    if (fm.save(manager_->getAll())) {
        std::cout << "已保存到文件。\n";
    } else {
        std::cout << "保存失败。\n";
    }
}

}  // namespace student_manager
