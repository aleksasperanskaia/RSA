#include "my_rsa.h"
#include <iostream>

// Проверка, является ли число простым
bool IsPrime(cpp_int n) {
    if (n <= 1) return false;
    for (cpp_int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Быстрое возведение в степень по модулю
cpp_int ModExponentiation(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Генерация закрытого ключа
cpp_int GeneratePrivateKey(cpp_int p, cpp_int q) {
    if (!IsPrime(p) || !IsPrime(q)) {
        std::cout << "Error: p and q must be prime numbers." << std::endl;
        return cpp_int(0);
    }
    cpp_int phi = (p - 1) * (q - 1);
    cpp_int e = 17;  // Новый публичный экспонент
    cpp_int d = 0;
    cpp_int k = 1;
    while (true) {
        cpp_int val = k * phi + 1;
        if (val % e == 0) {
            d = val / e;
            break;
        }
        ++k;
    }
    return d;
}

// Преобразование строки в число
cpp_int ConvertTextToNumber(const std::string &text) {
    cpp_int num = 0;
    for (char c : text) {
        num = num * 256 + static_cast<unsigned char>(c);
    }
    return num;
}

// Преобразование числа в строку
std::string ConvertNumberToText(cpp_int num) {
    std::string text;
    while (num > 0) {
        text.insert(text.begin(), static_cast<char>(num % 256));
        num /= 256;
    }
    return text;
}

// Шифрование блока текста
cpp_int EncryptMessageBlock(cpp_int m, cpp_int e, cpp_int n) {
    return ModExponentiation(m, e, n);
}

// Дешифрование блока текста
cpp_int DecryptMessageBlock(cpp_int c, cpp_int d, cpp_int n) {
    return ModExponentiation(c, d, n);
}

// Шифрование текста
std::vector<cpp_int> EncryptFullText(const std::string &message, cpp_int e, cpp_int n, cpp_int blockSize) {
    std::vector<cpp_int> encryptedBlocks;
    for (size_t i = 0; i < message.size(); i += blockSize.convert_to<size_t>()) {
        std::string block = message.substr(i, blockSize.convert_to<size_t>());
        cpp_int m = ConvertTextToNumber(block);
        encryptedBlocks.push_back(EncryptMessageBlock(m, e, n));
    }
    return encryptedBlocks;
}

// Дешифрование текста
std::string DecryptFullText(const std::vector<cpp_int> &encryptedBlocks, cpp_int d, cpp_int n) {
    std::string decryptedMessage;
    for (const cpp_int &block : encryptedBlocks) {
        cpp_int decryptedBlock = DecryptMessageBlock(block, d, n);
        decryptedMessage += ConvertNumberToText(decryptedBlock);
    }
    return decryptedMessage;
}
