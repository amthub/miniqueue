#include <iostream>
#include "log.h"

int main() {
    Log log("test.log");
    uint64_t a = log.append("hello");
    uint64_t b = log.append("world");
    std::cout << "read " << a << ": " << log.read(a) << std::endl;
    std::cout << "read " << b << ": " << log.read(b) << std::endl;
    return 0;
}