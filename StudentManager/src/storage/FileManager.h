#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "core/Student.h"
#include "core/StudentManager.h"
#include <string>
#include <fstream>
#include <vector>

namespace student_manager {
namespace storage {

// RAII：不持有长期句柄，每次 load/save 打开即关闭；路径与策略由构造时绑定
class FileManager {
public:
    explicit FileManager(const std::string& filePath);
    ~FileManager() = default;

    // 禁止拷贝
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    bool load(StudentManager& out);
    bool save(const StudentManager::Container& students);

private:
    std::string path_;
};

}  // namespace storage
}  // namespace student_manager

#endif  // FILE_MANAGER_H
