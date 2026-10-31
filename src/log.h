#pragma once
#include <cstdint>
#include <fstream>
#include <string>

class Log {
public:
    explicit Log(const std::string& path);
    uint64_t append(const std::string& message);
    std::string read(uint64_t offset);

private:
    void recover();
    std::string path_;
    std::ofstream out_;
    uint64_t next_offset_ = 0;
};