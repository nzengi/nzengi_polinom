#include <iostream>
#include "little_endian_encryption.hpp"
#include "utils.hpp"

int main() {
    // Define polynomial coefficients and modulus value
    std::vector<int> coefficients = {3, 5, 7, 9, 11};  // Example coefficients
    int p = 29;  // Prime number

    try {
        LittleEndianEncryption leEnc(coefficients, p);

        // Example decimal input
        int decimal_input = 123456;

        // Convert to little endian binary
        std::string little_endian_binary = leEnc.toLittleEndian(decimal_input);
        std::cout << "Little Endian Binary: " << little_endian_binary << std::endl;

        // Validate binary string
        if (!Utils::validateBinaryString(little_endian_binary)) {
            throw std::invalid_argument("Invalid binary string format.");
        }

        // Encryption
        int encrypted_value = leEnc.encrypt(little_endian_binary);
        std::cout << "Encrypted Value (Decimal): " << encrypted_value << std::endl;

        // Decryption
        int decrypted_value = leEnc.decrypt(encrypted_value);
        std::cout << "Decrypted Value (Decimal): " << decrypted_value << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
