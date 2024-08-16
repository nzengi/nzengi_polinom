#include <iostream>
#include <vector>
#include <random>
#include <functional>  // For hash

class AdvancedPolynomialEncryption {
private:
    std::vector<int> coefficients;  // Dynamic coefficients of the polynomial
    std::vector<int> moduli;  // Multiple modulus values for added security

public:
    // Constructor to initialize polynomial coefficients and modulus values
    AdvancedPolynomialEncryption(const std::vector<int>& coeffs, const std::vector<int>& mods)
        : coefficients(coeffs), moduli(mods) {}

    // Function to generate dynamic coefficients based on a hash of the key
    std::vector<int> generateDynamicCoefficients(const std::string& key) {
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(key);

        std::vector<int> dynamic_coefficients(coefficients.size());
        for (size_t i = 0; i < coefficients.size(); ++i) {
            dynamic_coefficients[i] = (coefficients[i] + hash_value) % moduli[i];
        }
        return dynamic_coefficients;
    }

    // Encryption function with multiple moduli
    std::vector<int> encrypt(const std::vector<int>& variables, const std::string& key) {
        std::vector<int> encrypted_values(moduli.size());
        std::vector<int> dynamic_coefficients = generateDynamicCoefficients(key);

        // Compute the polynomial using the provided variables and dynamic coefficients
        for (size_t j = 0; j < moduli.size(); ++j) {
            int result = 0;
            for (size_t i = 0; i < dynamic_coefficients.size() && i < variables.size(); ++i) {
                result += dynamic_coefficients[i] * pow(variables[i], 2);  // Example with squared variables
            }
            // Apply modular arithmetic for each modulus
            encrypted_values[j] = result % moduli[j];
            encrypted_values[j] = (encrypted_values[j] < 0) ? encrypted_values[j] + moduli[j] : encrypted_values[j];
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
                original_value += dynamic_coefficients[i] * pow(variables[i], 2);  // Reverse the polynomial calculation
            }

            // Apply modular arithmetic for each modulus
            decrypted_values[j] = original_value % moduli[j];
            decrypted_values[j] = (decrypted_values[j] < 0) ? decrypted_values[j] + moduli[j] : decrypted_values[j];
        }

        return decrypted_values;
    }
};

int main() {
    // Define the base polynomial coefficients and multiple modulus values
    std::vector<int> coefficients = {3, 5, 7, 9};  // Example base coefficients
    std::vector<int> moduli = {29, 31, 37};  // Multiple modulus values for added security

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

    return 0;
}
