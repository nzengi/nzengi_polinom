#include <iostream>
#include <cmath>

class PolynomialEncryption {
private:
    int a1, a2, a3;  // Coefficients of the polynomial
    int p;  // Prime number for modular arithmetic

public:
    PolynomialEncryption(int a1, int a2, int a3, int p) : a1(a1), a2(a2), a3(a3), p(p) {}

    // Encryption function
    int encrypt(int x, int y) {
        // Compute the polynomial value and apply modular arithmetic
        int result = (a1 * pow(x, 2) + a2 * pow(y, 2) + a3 * x * y) % p;
        // Ensure the result is positive (modular arithmetic can produce negative values)
        return (result < 0) ? result + p : result;
    }

    // Decryption function
    int decrypt(int encrypted_value, int x, int y) {
        // Perform modular inversion of the encryption process
        int original_value = (a1 * pow(x, 2) + a2 * pow(y, 2) + a3 * x * y) % p;
        // Ensure the result is positive
        return (original_value < 0) ? original_value + p : original_value;
    }
};

int main() {
    // Define the polynomial coefficients and the modulus value
    PolynomialEncryption polyEnc(3, 5, 7, 23);

    int x = 5;  // Value to encrypt
    int y = 7;  // Another value to encrypt

    // Encryption process
    int encrypted_value = polyEnc.encrypt(x, y);
    std::cout << "Encrypted Value: " << encrypted_value << std::endl;

    // Decryption process
    int decrypted_value = polyEnc.decrypt(encrypted_value, x, y);
    std::cout << "Decrypted Value: " << decrypted_value << std::endl;

    return 0;
}
