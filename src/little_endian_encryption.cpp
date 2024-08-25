#include "little_endian_encryption.hpp"
#include <bitset>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "utils.hpp"

// Constructor to initialize polynomial coefficients and modulus
LittleEndianEncryption::LittleEndianEncryption(const std::vector<int>& coeffs, int p) : coefficients(coeffs), p(p) {
    if (!Utils::isPrime(p)) {
        throw std::invalid_argument("Modulus must be a prime number.");
    }
}

// Convert decimal to little endian binary
std::string LittleEndianEncryption::toLittleEndian(int num) {
    std::string binary = std::bitset<32>(num).to_string();
    std::reverse(binary.begin(), binary.end());
    return binary;
}

// Convert little endian binary back to decimal
int LittleEndianEncryption::fromLittleEndian(const std::string& little_endian_binary) {
    std::string binary = little_endian_binary;
    std::reverse(binary.begin(), binary.end());
    return std::bitset<32>(binary).to_ulong();
}

// Encryption process
int LittleEndianEncryption::encrypt(const std::string& little_endian_binary) {
    int result = 0;
    size_t len = std::min(little_endian_binary.size(), coefficients.size());

    for (size_t i = 0; i < len; ++i) {
        if (little_endian_binary[i] == '1') {
            result += coefficients[i] * static_cast<int>(pow(2, i));
        }
    }

    result %= p;
    return result;
}

// Decryption process (simplified)
int LittleEndianEncryption::decrypt(int encrypted_value) {
    return encrypted_value % p;
}
