#include "core/Menu.h"
#include <iostream>

int main() {
    // 数据文件路径：运行时请在工作目录为 StudentManager 根目录下执行（或保证 data/ 存在）
    const std::string dataPath = "data/students.txt";
    student_manager::Menu menu(dataPath);
    menu.run();
    return 0;
}
