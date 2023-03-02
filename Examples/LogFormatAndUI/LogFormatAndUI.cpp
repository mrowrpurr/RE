// 1. Formatting
#include <string_format.h>
// 2. Logging
// 3. UI

#include <iostream>

int main() {
    auto num = 69;
    std::cout << string_format("FMT The number is: {}", num) << std::endl;
    return 0;
}
