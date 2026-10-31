#include <fstream>
#include <iostream>
#include "log.h"

int main() {
    {
        Log log("crash.log");
        log.append("hello");
    }
    {
        // simulate a crash: a record claiming 100 bytes but holding only 3
        std::ofstream raw("crash.log", std::ios::binary | std::ios::app);
        uint32_t fake_len = 100;
        raw.write(reinterpret_cast<const char*>(&fake_len), sizeof(fake_len));
        raw.write("abc", 3);
    }

    Log log("crash.log");
    uint64_t off = log.append("world");
    std::cout << "offset " << off << std::endl;
    std::cout << "read 0: " << log.read(0) << std::endl;
    std::cout << "read " << off << ": " << log.read(off) << std::endl;
    return 0;
}