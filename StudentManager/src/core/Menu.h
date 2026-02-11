#ifndef MENU_H
#define MENU_H

#include "core/StudentManager.h"
#include "storage/FileManager.h"
#include <memory>
#include <string>

namespace student_manager {

class Menu {
public:
    explicit Menu(const std::string& dataPath);
    void run();

private:
    void showMainMenu();
    void addStudent();
    void removeStudent();
    void findStudent();
    void updateStudent();
    void listStudents();
    void loadFromFile();
    void saveToFile();
    void printStudent(const Student& s) const;

    std::unique_ptr<StudentManager> manager_;
    std::string dataPath_;
};

}  // namespace student_manager

#endif  // MENU_H
