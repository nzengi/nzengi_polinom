#include <iostream>
#include <bitset>
#include <string>
#include <vector>

class BinaryEncryption {
private:
    std::vector<int> coefficients;  // Dynamic coefficients of the polynomial
    int p;  // Modulus value for modular arithmetic

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

    // Encryption function (example using binary)
    std::string encrypt(const std::string& binary_input) {
        int result = 0;
        
        // Simple encryption logic using binary (can be expanded)
        for (size_t i = 0; i < binary_input.length(); ++i) {
            if (binary_input[i] == '1') {
                result += coefficients[i % coefficients.size()];
            }
        }

        result %= p;
        return std::bitset<16>(result).to_string();  // Convert the result to binary format
    }

    // Decryption function (example using binary)
    std::string decrypt(const std::string& encrypted_binary) {
        int result = std::bitset<16>(encrypted_binary).to_ulong();  // Convert binary to integer
        
        // Simple decryption logic (reverse of encryption)
        return std::bitset<16>(result).to_string();  // Return binary string as result
    }
};

int main() {
    // Define polynomial coefficients and modulus value
    std::vector<int> coefficients = {3, 5, 7, 9};  // Example coefficients for the polynomial
    int p = 29;  // Prime number for modular arithmetic

    BinaryEncryption binEnc(coefficients, p);

    // Example hexadecimal input (7-digit)
    std::string hex_input = "1a2f3b";

    // Convert hex to binary
    std::string binary_input = binEnc.hexToBinary(hex_input);
    std::cout << "Binary Input: " << binary_input << std::endl;

    // Encryption process
    std::string encrypted_binary = binEnc.encrypt(binary_input);
    std::cout << "Encrypted Binary: " << encrypted_binary << std::endl;

    // Decryption process
    std::string decrypted_binary = binEnc.decrypt(encrypted_binary);
    std::cout << "Decrypted Binary: " << decrypted_binary << std::endl;

    // Convert decrypted binary back to hex
    std::string decrypted_hex = binEnc.binaryToHex(decrypted_binary);
    std::cout << "Decrypted Hex: " << decrypted_hex << std::endl;

    return 0;
}
