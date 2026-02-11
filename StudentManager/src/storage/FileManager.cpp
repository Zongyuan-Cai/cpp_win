#include "storage/FileManager.h"
#include <fstream>
#include <iostream>

namespace student_manager {
namespace storage {

FileManager::FileManager(const std::string& filePath) : path_(filePath) {}

bool FileManager::load(StudentManager& out) {
    std::ifstream ifs(path_);
    if (!ifs.is_open()) {
        return false;
    }
    out.clear();
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        try {
            out.add(Student::fromLine(line));
        } catch (...) {
            // 跳过非法行
        }
    }
    return true;
}

bool FileManager::save(const StudentManager::Container& students) {
    std::ofstream ofs(path_);
    if (!ofs.is_open()) {
        return false;
    }
    for (const auto& s : students) {
        ofs << s.toLine() << '\n';
    }
    return ofs.good();
}

}  // namespace storage
}  // namespace student_manager
