#ifndef VIGENERE_H
#define VIGENERE_H

#include <string>
#include <vector>

std::string vigenereCipher(std::string input, std::string key);

std::string vigenereDecipher(std::string input, std::string key);

std::string vigenereDecipherWithoutKey(std::string input);

int keyLength(std::string str);

std::vector<std::string> partition(std::string str, int keyLen);

std::string getKey(std::string str, int keyLen);

#endif // VIGENERE_H
