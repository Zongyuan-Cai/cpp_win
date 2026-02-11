#include "core/Student.h"
#include <sstream>
#include <stdexcept>
#include <vector>

namespace student_manager {

namespace {
const char DELIM = '|';
const int EXPECTED_FIELDS = 5;
}  // namespace

std::string Student::toLine() const {
    std::ostringstream oss;
    oss << id << DELIM << name << DELIM << major << DELIM << age << DELIM << score;
    return oss.str();
}

Student Student::fromLine(const std::string& line) {
    std::istringstream iss(line);
    std::string part;
    std::vector<std::string> parts;
    while (std::getline(iss, part, DELIM)) {
        parts.push_back(part);
    }
    if (parts.size() != static_cast<size_t>(EXPECTED_FIELDS)) {
        throw std::runtime_error("Invalid student line: " + line);
    }
    Student s;
    s.id = static_cast<std::uint32_t>(std::stoul(parts[0]));
    s.name = parts[1];
    s.major = parts[2];
    s.age = std::stoi(parts[3]);
    s.score = std::stod(parts[4]);
    return s;
}

}  // namespace student_manager
