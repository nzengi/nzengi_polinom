#include <iostream>
#include <vector>
#include <random>
#include <cmath> // For std::pow
#include <stdexcept> // For std::runtime_error

class AdvancedPolynomialEncryption {
private:
    std::vector<int> coefficients;  // Dynamic coefficients of the polynomial
    std::vector<int> moduli;  // Multiple modulus values for added security

    // Helper function to compute modular exponentiation
    int modularPow(int base, int exponent, int modulus) {
        int result = 1;
        base = base % modulus;
        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = (result * base) % modulus;
            }
            exponent = exponent >> 1;
            base = (base * base) % modulus;
        }
        return result;
    }

public:
    // Constructor to initialize polynomial coefficients and modulus values
    AdvancedPolynomialEncryption(const std::vector<int>& coeffs, const std::vector<int>& mods)
        : coefficients(coeffs), moduli(mods) {
        if (coeffs.size() != mods.size()) {
            throw std::runtime_error("Coefficients and moduli must have the same size");
        }
    }

    // Function to generate dynamic coefficients based on a hash of the key
    std::vector<int> generateDynamicCoefficients(const std::string& key) {
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(key);

        std::vector<int> dynamic_coefficients(coefficients.size());
        for (size_t i = 0; i < coefficients.size(); ++i) {
            dynamic_coefficients[i] = (coefficients[i] + static_cast<int>(hash_value)) % moduli[i];
        }
        return dynamic_coefficients;
    }

    // Encryption function with multiple moduli
    std::vector<int> encrypt(const std::vector<int>& variables, const std::string& key) {
        std::vector<int> encrypted_values(moduli.size());
        std::vector<int> dynamic_coefficients = generateDynamicCoefficients(key);

        for (size_t j = 0; j < moduli.size(); ++j) {
            int result = 0;
            for (size_t i = 0; i < dynamic_coefficients.size() && i < variables.size(); ++i) {
                result = (result + dynamic_coefficients[i] * modularPow(variables[i], 2, moduli[j])) % moduli[j];
            }
            encrypted_values[j] = result;
        }

        return encrypted_values;
    }

    // Decryption function with multiple moduli
    std::vector<int> decrypt(const std::vector<int>& encrypted_values, const std::vector<int>& variables, const std::string& key) {
        std::vector<int> decrypted_values(moduli.size());
        std::vector<int> dynamic_coefficients = generateDynamicCoefficients(key);

        for (size_t j = 0; j < moduli.size(); ++j) {
            int original_value = 0;
            for (size_t i = 0; i < dynamic_coefficients.size() && i < variables.size(); ++i) {
                original_value = (original_value + dynamic_coefficients[i] * modularPow(variables[i], 2, moduli[j])) % moduli[j];
            }

            decrypted_values[j] = original_value;
        }

        return decrypted_values;
    }
};

int main() {
    // Define the base polynomial coefficients and multiple modulus values
    std::vector<int> coefficients = {3, 5, 7, 9};  // Example base coefficients
    std::vector<int> moduli = {29, 31, 37};  // Multiple modulus values for added security

    try {
        AdvancedPolynomialEncryption polyEnc(coefficients, moduli);

        // Example key and variables for encryption
        std::string key = "abc123";
        std::vector<int> variables = {5, 7, 3, 4};  // Example variables

        // Encryption process
        std::vector<int> encrypted_values = polyEnc.encrypt(variables, key);
        std::cout << "Encrypted Values: ";
        for (int val : encrypted_values) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Decryption process
        std::vector<int> decrypted_values = polyEnc.decrypt(encrypted_values, variables, key);
        std::cout << "Decrypted Values: ";
        for (int val : decrypted_values) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
