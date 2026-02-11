#include "core/StudentManager.h"
#include <algorithm>

namespace student_manager {

StudentManager::Container::iterator StudentManager::findIt(std::uint32_t id) {
    return std::find_if(students_.begin(), students_.end(),
                        [id](const Student& s) { return s.id == id; });
}

StudentManager::Container::const_iterator StudentManager::findIt(std::uint32_t id) const {
    return std::find_if(students_.begin(), students_.end(),
                        [id](const Student& s) { return s.id == id; });
}

bool StudentManager::add(const Student& s) {
    if (findIt(s.id) != students_.end()) {
        return false;
    }
    students_.push_back(s);
    return true;
}

bool StudentManager::remove(std::uint32_t id) {
    auto it = findIt(id);
    if (it == students_.end()) {
        return false;
    }
    students_.erase(it);
    return true;
}

std::optional<Student> StudentManager::find(std::uint32_t id) const {
    auto it = findIt(id);
    if (it == students_.end()) {
        return std::nullopt;
    }
    return *it;
}

bool StudentManager::update(std::uint32_t id, const Student& s) {
    auto it = findIt(id);
    if (it == students_.end()) {
        return false;
    }
    *it = s;
    return true;
}

void StudentManager::sortById() {
    std::sort(students_.begin(), students_.end(),
              [](const Student& a, const Student& b) { return a.id < b.id; });
}

void StudentManager::sortByScore() {
    std::sort(students_.begin(), students_.end(),
              [](const Student& a, const Student& b) { return a.score > b.score; });
}

}  // namespace student_manager
