#include <iostream>
#include "log.h"

int main() {
    Log log("test.log");
    std::cout << "offset " << log.append("hello") << std::endl;
    std::cout << "offset " << log.append("world") << std::endl;
    return 0;
}