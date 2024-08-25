#include "utils.hpp"
#include <cmath>
#include <regex>

bool Utils::isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

bool Utils::validateBinaryString(const std::string& binary_str) {
    std::regex binary_pattern("^[01]+$");
    return std::regex_match(binary_str, binary_pattern);
}
