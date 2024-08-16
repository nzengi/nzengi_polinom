#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cmath>

class BinaryEncryption {
private:
    std::vector<int> coefficients;  // Coefficients of the polynomial
    int p;  // Prime number for modular arithmetic

public:
    // Constructor to initialize polynomial coefficients and modulus
    BinaryEncryption(const std::vector<int>& coeffs, int p) : coefficients(coeffs), p(p) {}

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
            }
        }
        return binary;
    }

    // Function to convert binary string to hexadecimal
    std::string binaryToHex(const std::string& binary) {
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
        // The decryption logic should reverse the encryption process
        // Assuming a simple modular inverse here (depending on the complexity of the encryption)
        return encrypted_value % p;  // This is a simplified version for demonstration
    }
};

int main() {
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

    // Optionally, convert decrypted value back to hex or binary format
    return 0;
}
