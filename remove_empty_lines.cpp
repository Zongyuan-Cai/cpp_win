#include <fstream>
#include <string>
#include <iostream>
#include <vector>

void process_file(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "无法打开 " << path << '\n';
        return;
    }
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    in.seekg(0);
    std::vector<char> buf(size);
    in.read(buf.data(), size);
    in.close();

    std::string raw(buf.begin(), buf.end());
    std::string content;
    size_t i = 0;
    bool first = true;

    while (i < raw.size()) {
        size_t line_start = i;
        while (i < raw.size() && raw[i] != '\n' && raw[i] != '\r') ++i;
        std::string line = raw.substr(line_start, i - line_start);
        while (i < raw.size() && (raw[i] == '\r' || raw[i] == '\n')) ++i;

        if (!line.empty()) {
            if (!first) content += '\n';
            content += line;
            first = false;
        }
    }

    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "无法写入 " << path << '\n';
        return;
    }
    out.write(content.data(), content.size());
    out.close();

    std::cout << path << ": 已删除空行\n";
}

int main(int argc, char* argv[]) {
    std::string files[] = {"book2.txt", "book3.txt", "book6.txt", "book7.txt"};
    if (argc > 1) {
        for (int i = 1; i < argc; ++i)
            process_file(argv[i]);
    } else {
        for (const auto& f : files)
            process_file(f);
    }
    return 0;
}
