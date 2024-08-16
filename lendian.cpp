#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <algorithm>

class LittleEndianEncryption {
private:
    std::vector<int> coefficients;  // Coefficients of the polynomial
    int p;  // Prime number for modular arithmetic

public:
    // Constructor to initialize polynomial coefficients and modulus
    LittleEndianEncryption(const std::vector<int>& coeffs, int p) : coefficients(coeffs), p(p) {}

    // Function to convert a decimal number to little endian binary string
    std::string toLittleEndian(int num) {
        std::string binary = std::bitset<32>(num).to_string();  // Convert to 32-bit binary
        std::reverse(binary.begin(), binary.end());  // Reverse the string to get little endian format
        return binary;
    }

    // Function to convert little endian binary string back to decimal number
    int fromLittleEndian(const std::string& little_endian_binary) {
        std::string binary = little_endian_binary;
        std::reverse(binary.begin(), binary.end());  // Reverse it back to normal binary format
        return std::bitset<32>(binary).to_ulong();  // Convert back to decimal
    }

    // Encryption function using polynomial and little endian binary input
    int encrypt(const std::string& little_endian_binary) {
        int result = 0;

        // Ensure little_endian_binary length matches coefficients size, if not adjust accordingly
        size_t len = std::min(little_endian_binary.size(), coefficients.size());

        // Compute the polynomial using little endian binary input
        for (size_t i = 0; i < len; ++i) {
            if (little_endian_binary[i] == '1') {
                result += coefficients[i] * pow(2, i);  // Use the binary position as exponent
            }
        }

        // Apply modular arithmetic
        result %= p;
        return result;
    }

    // Decryption function (reverse of encryption)
    int decrypt(int encrypted_value) {
        // The decryption logic should reverse the encryption process
        // Assuming a simple modular inverse here (depending on the complexity of the encryption)
        return encrypted_value % p;  // This is a simplified version for demonstration
    }
};

int main() {
    // Define polynomial coefficients and modulus value
    std::vector<int> coefficients = {3, 5, 7, 9, 11};  // Example coefficients for the polynomial
    int p = 29;  // Prime number for modular arithmetic

    LittleEndianEncryption leEnc(coefficients, p);

    // Example decimal input
    int decimal_input = 123456;

    // Convert decimal input to little endian binary
    std::string little_endian_binary = leEnc.toLittleEndian(decimal_input);
    std::cout << "Little Endian Binary: " << little_endian_binary << std::endl;

    // Encryption process
    int encrypted_value = leEnc.encrypt(little_endian_binary);
    std::cout << "Encrypted Value (Decimal): " << encrypted_value << std::endl;

    // Decryption process
    int decrypted_value = leEnc.decrypt(encrypted_value);
    std::cout << "Decrypted Value (Decimal): " << decrypted_value << std::endl;

    return 0;
}
