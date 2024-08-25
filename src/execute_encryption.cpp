#include <iostream>
#include "polynomial_encryption.hpp"
#include "utils.hpp"

int main() {
    // Define the polynomial coefficients and the modulus value
    PolynomialEncryption polyEnc(3, 5, 7, 23);

    int x = 5;  // Value to encrypt
    int y = 7;  // Another value to encrypt

    if (!Utils::validateInput(x, y)) {
        std::cerr << "Invalid input values." << std::endl;
        return 1;
    }

    // Encryption process
    int encrypted_value = polyEnc.encrypt(x, y);
    std::cout << "Encrypted Value: " << encrypted_value << std::endl;

    // Decryption process
    int decrypted_value = polyEnc.decrypt(encrypted_value, x, y);
    std::cout << "Decrypted Value: " << decrypted_value << std::endl;

    return 0;
}
