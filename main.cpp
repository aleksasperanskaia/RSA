#include "my_rsa.h"
#include <iostream>

int main() {
    cpp_int p = 2305843009213693951;
    cpp_int q = 18014398241046527;

    cpp_int d = GeneratePrivateKey(p, q);
    cpp_int e = 17;  // Новый публичный экспонент
    cpp_int n = p * q;
    cpp_int blockSize = 8;

    std::string message = "12345678";
    std::cout << "Original message: " << message << std::endl;

    // Шифрование
    std::vector<cpp_int> encryptedMessage = EncryptFullText(message, e, n, blockSize);
    std::cout << "Encrypted message: ";
    for (const auto &block : encryptedMessage) {
        std::cout << block << " ";
    }
    std::cout << std::endl;

    // Дешифрование
    std::string decryptedMessage = DecryptFullText(encryptedMessage, d, n);
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}
