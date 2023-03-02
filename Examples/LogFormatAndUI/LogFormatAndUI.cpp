// 1. Formatting
// 2. Logging
// 3. UI

// #include <format>
#include <iostream>

int main() {
    auto num = 69;
    std::cout << std::format("The number is: {}", num) << std::endl;
    return 0;
}
