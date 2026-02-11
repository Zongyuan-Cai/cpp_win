#include "utils/Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>

namespace student_manager {
namespace utils {

namespace {
std::string getLine() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}
}  // namespace

std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt << ": ";
    return trim(getLine());
}

int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt << ": ";
        std::string line = getLine();
        try {
            if (!line.empty()) {
                return std::stoi(line);
            }
        } catch (...) {}
        std::cout << "请输入有效整数。\n";
    }
}

std::uint64_t readUInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt << ": ";
        std::string line = getLine();
        try {
            if (!line.empty()) {
                unsigned long v = std::stoul(line);
                return static_cast<std::uint64_t>(v);
            }
        } catch (...) {}
        std::cout << "请输入有效非负整数。\n";
    }
}

double readDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt << ": ";
        std::string line = getLine();
        try {
            if (!line.empty()) {
                return std::stod(line);
            }
        } catch (...) {}
        std::cout << "请输入有效数字。\n";
    }
}

int readIntDefault(const std::string& prompt, int defaultVal) {
    std::cout << prompt << ": ";
    std::string line = trim(getLine());
    if (line.empty()) return defaultVal;
    try {
        return std::stoi(line);
    } catch (...) {
        return defaultVal;
    }
}

double readDoubleDefault(const std::string& prompt, double defaultVal) {
    std::cout << prompt << ": ";
    std::string line = trim(getLine());
    if (line.empty()) return defaultVal;
    try {
        return std::stod(line);
    } catch (...) {
        return defaultVal;
    }
}

}  // namespace utils
}  // namespace student_manager
