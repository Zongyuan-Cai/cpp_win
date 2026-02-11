#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdint>

namespace student_manager {
namespace utils {

std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt);
std::uint64_t readUInt(const std::string& prompt);
double readDouble(const std::string& prompt);
// 若直接回车则返回 defaultVal
int readIntDefault(const std::string& prompt, int defaultVal);
double readDoubleDefault(const std::string& prompt, double defaultVal);

std::string trim(const std::string& s);

}  // namespace utils
}  // namespace student_manager

#endif  // UTILS_H
