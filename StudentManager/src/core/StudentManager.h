#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "core/Student.h"
#include <vector>
#include <optional>
#include <cstdint>

namespace student_manager {

class StudentManager {
public:
    using Container = std::vector<Student>;

    bool add(const Student& s);
    bool remove(std::uint32_t id);
    std::optional<Student> find(std::uint32_t id) const;
    bool update(std::uint32_t id, const Student& s);

    const Container& getAll() const { return students_; }
    void clear() { students_.clear(); }

    // 按 ID 排序（原地）
    void sortById();
    // 按分数排序（原地）
    void sortByScore();

private:
    Container students_;
    Container::iterator findIt(std::uint32_t id);
    Container::const_iterator findIt(std::uint32_t id) const;
};

}  // namespace student_manager

#endif  // STUDENT_MANAGER_H
