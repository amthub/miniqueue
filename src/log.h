#pragma once
#include <cstdint>
#include <fstream>
#include <string>

class Log {
public:
    explicit Log(const std::string& path);
    uint64_t append(const std::string& message);

private:
    std::ofstream out_;
    uint64_t next_offset_ = 0;
};