#include <iostream>
#include "log.h"

int main() {
    Log log("index.log");
    std::cout << "start: " << log.append("hello") << std::endl;
    std::cout << "next: " << log.append("world") << std::endl;
    std::cout << "read 0: " << log.read(0) << std::endl;
    std::cout << "read 1: " << log.read(1) << std::endl;
    try {
        log.read(99);
    } catch (const std::out_of_range& e) {
        std::cout << "error: " << e.what() << std::endl;
    }
    return 0;
}