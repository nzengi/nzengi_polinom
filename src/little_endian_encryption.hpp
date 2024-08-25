#ifndef LITTLE_ENDIAN_ENCRYPTION_HPP
#define LITTLE_ENDIAN_ENCRYPTION_HPP

#include <vector>
#include <string>

class LittleEndianEncryption {
private:
    std::vector<int> coefficients;  // Coefficients of the polynomial
    int p;  // Prime number for modular arithmetic

public:
    LittleEndianEncryption(const std::vector<int>& coeffs, int p);

    // Convert a decimal number to little endian binary string
    std::string toLittleEndian(int num);

    // Convert little endian binary string back to decimal number
    int fromLittleEndian(const std::string& little_endian_binary);

    // Encryption using polynomial and little endian binary input
    int encrypt(const std::string& little_endian_binary);

    // Decryption (reverse of encryption)
    int decrypt(int encrypted_value);
};

#endif // LITTLE_ENDIAN_ENCRYPTION_HPP
