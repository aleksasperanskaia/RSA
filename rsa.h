#ifndef MY_RSA_H
#define MY_RSA_H

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>

using namespace boost::multiprecision;

// Проверка, является ли число простым
bool IsPrime(cpp_int n);

// Быстрое возведение в степень по модулю
cpp_int ModExponentiation(cpp_int base, cpp_int exp, cpp_int mod);

// Генерация закрытого ключа
cpp_int GeneratePrivateKey(cpp_int p, cpp_int q);

// Преобразование строки в число
cpp_int ConvertTextToNumber(const std::string &text);

// Преобразование числа в строку
std::string ConvertNumberToText(cpp_int num);

// Шифрование блока текста
cpp_int EncryptMessageBlock(cpp_int m, cpp_int e, cpp_int n);

// Дешифрование блока текста
cpp_int DecryptMessageBlock(cpp_int c, cpp_int d, cpp_int n);

// Шифрование текста
std::vector<cpp_int> EncryptFullText(const std::string &message, cpp_int e, cpp_int n, cpp_int blockSize);

// Дешифрование текста
std::string DecryptFullText(const std::vector<cpp_int> &encryptedBlocks, cpp_int d, cpp_int n);

#endif // MY_RSA_H
