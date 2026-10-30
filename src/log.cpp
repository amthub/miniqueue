#include "log.h"
#include <stdexcept>

Log::Log(const std::string& path)
    : out_(path, std::ios::binary | std::ios::app) {
    if (!out_) {
        throw std::runtime_error("cannot open log file: " + path);
    }
}

uint64_t Log::append(const std::string& message) {
    uint32_t len = static_cast<uint32_t>(message.size());
    out_.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out_.write(message.data(), len);
    out_.flush();
    return next_offset_++;
}