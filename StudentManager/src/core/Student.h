#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <cstdint>

namespace student_manager {

struct Student {
    std::uint32_t id{0};
    std::string name;
    std::string major;
    int age{0};
    double score{0.0};

    Student() = default;
    Student(std::uint32_t id_, const std::string& name_, const std::string& major_,
           int age_, double score_)
        : id(id_), name(name_), major(major_), age(age_), score(score_) {}

    std::string toLine() const;   // 序列化为一行文本（用于文件存储）
    static Student fromLine(const std::string& line);  // 从一行文本反序列化
};

}  // namespace student_manager

#endif  // STUDENT_H
