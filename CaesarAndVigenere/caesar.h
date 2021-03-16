#ifndef CAESAR_H
#define CAESAR_H

#include <string>
#include <vector>
#include <tuple>

std::string caesarCipher(std::string input, int shift);

std::string caesarDecipher(std::string input, int shift);

std::string caesarDecipherWithoutKey(std::string input);

int findShift(std::string str);

std::vector<std::tuple<int, std::string, double>> bruteShift(std::string str);

#endif // CAESAR_H
