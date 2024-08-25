#include "polynomial_encryption.hpp"
#include <cmath>

// Constructor to initialize polynomial coefficients and modulus
PolynomialEncryption::PolynomialEncryption(int a1, int a2, int a3, int p) : a1(a1), a2(a2), a3(a3), p(p) {}

// Encryption process
int PolynomialEncryption::encrypt(int x, int y) {
    int result = (a1 * pow(x, 2) + a2 * pow(y, 2) + a3 * x * y) % p;
    return (result < 0) ? result + p : result;
}

// Decryption process
int PolynomialEncryption::decrypt(int encrypted_value, int x, int y) {
    int original_value = (a1 * pow(x, 2) + a2 * pow(y, 2) + a3 * x * y) % p;
    return (original_value < 0) ? original_value + p : original_value;
}
