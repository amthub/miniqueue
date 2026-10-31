#include<filesystem>
#include "log.h"
#include <stdexcept>

Log::Log(const std::string& path) : path_(path) {
    recover();
    out_.open(path_, std::ios::binary | std::ios::app);
    if (!out_) {
        throw std::runtime_error("cannot open log file: " + path);
    }
}

void Log::recover() {
    uint64_t size = 0;
    uint64_t valid = 0;
    uint64_t count = 0;

    {
        std::ifstream in(path_, std::ios::binary);
        if (!in) {
            next_offset_ = 0;
            return;  // file does not exist yet, nothing to recover
        }

        in.seekg(0, std::ios::end);
        size = static_cast<uint64_t>(in.tellg());
        in.seekg(0, std::ios::beg);

        uint32_t len = 0;
        while (valid + sizeof(len) <= size) {
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            if (valid + sizeof(len) + len > size) {
                break;  // incomplete record at the end
            }
            in.seekg(len, std::ios::cur);
            valid += sizeof(len) + len;
            ++count;
        }
    }

    next_offset_ = count;
    if (valid < size) {
        std::filesystem::resize_file(path_, valid);
    }
}

uint64_t Log::append(const std::string& message) {
    uint32_t len = static_cast<uint32_t>(message.size());
    out_.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out_.write(message.data(), len);
    out_.flush();
    return next_offset_++;
}

std::string Log::read(uint64_t offset) {
    std::ifstream in(path_, std::ios::binary);
    if (!in) {
        throw std::runtime_error("cannot open log file for reading: " + path_);
    }

    uint64_t current = 0;
    uint32_t len = 0;
    while (in.read(reinterpret_cast<char*>(&len), sizeof(len))) {
        if (current == offset) {
            std::string message(len, '\0');
            in.read(&message[0], len);
            if (!in) {
                throw std::runtime_error("log file is truncated");
            }
            return message;
        }
        in.seekg(len, std::ios::cur);
        ++current;
    }
    throw std::out_of_range("offset not found: " + std::to_string(offset));
}