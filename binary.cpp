#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

class BinaryEncryption {
private:
    std::vector<int> coefficients;  // Coefficients of the polynomial
    int p;  // Prime number for modular arithmetic

    // Helper function to calculate modular inverse using Extended Euclidean Algorithm
    int modularInverse(int a, int mod) {
        int m0 = mod, t, q;
        int x0 = 0, x1 = 1;

        if (mod == 1)
            return 0;

        while (a > 1) {
            // q is quotient
            q = a / mod;
            t = mod;

            // mod is remainder now, process same as Euclid's algo
            mod = a % mod, a = t;

            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }

        // Make x1 positive
        if (x1 < 0)
            x1 += m0;

        return x1;
    }

public:
    // Constructor to initialize polynomial coefficients and modulus
    BinaryEncryption(const std::vector<int>& coeffs, int p) : coefficients(coeffs), p(p) {
        if (p <= 0) {
            throw std::invalid_argument("Modulus p must be a positive integer.");
        }
    }

    // Function to convert a hexadecimal string to binary
    std::string hexToBinary(const std::string& hex) {
        std::string binary;
        for (char hex_char : hex) {
            switch (hex_char) {
                case '0': binary += "0000"; break;
                case '1': binary += "0001"; break;
                case '2': binary += "0010"; break;
                case '3': binary += "0011"; break;
                case '4': binary += "0100"; break;
                case '5': binary += "0101"; break;
                case '6': binary += "0110"; break;
                case '7': binary += "0111"; break;
                case '8': binary += "1000"; break;
                case '9': binary += "1001"; break;
                case 'a': case 'A': binary += "1010"; break;
                case 'b': case 'B': binary += "1011"; break;
                case 'c': case 'C': binary += "1100"; break;
                case 'd': case 'D': binary += "1101"; break;
                case 'e': case 'E': binary += "1110"; break;
                case 'f': case 'F': binary += "1111"; break;
                default:
                    throw std::invalid_argument("Invalid hexadecimal character.");
            }
        }
        return binary;
    }

    // Function to convert binary string to hexadecimal
    std::string binaryToHex(const std::string& binary) {
        if (binary.length() % 4 != 0) {
            throw std::invalid_argument("Binary string length must be a multiple of 4.");
        }

        std::string hex;
        for (size_t i = 0; i < binary.length(); i += 4) {
            std::string nibble = binary.substr(i, 4);
            if (nibble == "0000") hex += '0';
            else if (nibble == "0001") hex += '1';
            else if (nibble == "0010") hex += '2';
            else if (nibble == "0011") hex += '3';
            else if (nibble == "0100") hex += '4';
            else if (nibble == "0101") hex += '5';
            else if (nibble == "0110") hex += '6';
            else if (nibble == "0111") hex += '7';
            else if (nibble == "1000") hex += '8';
            else if (nibble == "1001") hex += '9';
            else if (nibble == "1010") hex += 'a';
            else if (nibble == "1011") hex += 'b';
            else if (nibble == "1100") hex += 'c';
            else if (nibble == "1101") hex += 'd';
            else if (nibble == "1110") hex += 'e';
            else if (nibble == "1111") hex += 'f';
        }
        return hex;
    }

    // Encryption function using polynomial and binary input
    int encrypt(const std::string& binary_input) {
        int result = 0;

        // Ensure binary_input length matches coefficients size, if not adjust accordingly
        size_t len = std::min(binary_input.size(), coefficients.size());

        // Compute the polynomial using binary input
        for (size_t i = 0; i < len; ++i) {
            if (binary_input[i] == '1') {
                result += coefficients[i] * pow(2, i);  // Use the binary position as exponent
            }
        }

        // Apply modular arithmetic
        result %= p;
        return result;
    }

    // Decryption function (reverse of encryption)
    int decrypt(int encrypted_value) {
        // Apply modular inverse if needed (this is a placeholder, real decryption logic may differ)
        return (encrypted_value * modularInverse(1, p)) % p;  // Simplified version
    }
};

int main() {
    try {
        // Define polynomial coefficients and modulus value
        std::vector<int> coefficients = {3, 5, 7, 9, 11};  // Example coefficients for the polynomial
        int p = 29;  // Prime number for modular arithmetic

        BinaryEncryption binEnc(coefficients, p);

        // Example hexadecimal input (7-digit)
        std::string hex_input = "1a2f3b";

        // Convert hex to binary
        std::string binary_input = binEnc.hexToBinary(hex_input);
        std::cout << "Binary Input: " << binary_input << std::endl;

        // Encryption process
        int encrypted_value = binEnc.encrypt(binary_input);
        std::cout << "Encrypted Value (Decimal): " << encrypted_value << std::endl;

        // Decryption process
        int decrypted_value = binEnc.decrypt(encrypted_value);
        std::cout << "Decrypted Value (Decimal): " << decrypted_value << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
