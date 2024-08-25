#ifndef POLYNOMIAL_ENCRYPTION_HPP
#define POLYNOMIAL_ENCRYPTION_HPP

class PolynomialEncryption {
private:
    int a1, a2, a3;  // Coefficients of the polynomial
    int p;  // Prime number for modular arithmetic

public:
    PolynomialEncryption(int a1, int a2, int a3, int p);

    // Encryption function
    int encrypt(int x, int y);

    // Decryption function
    int decrypt(int encrypted_value, int x, int y);
};

#endif // POLYNOMIAL_ENCRYPTION_HPP
