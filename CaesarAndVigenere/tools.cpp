#include "tools.h"

#include <locale>
#include <iostream>
#include <cmath>

std::string removeAccent(std::__cxx11::string str)
{
    std::string accent = "æèéêëàáâãäåìíîïòóôõöùúûüÆÈÉÊËÀÁÂÃÄÅÌÍÎÏÒÓÔÕÖÙÚÛÜ";
    std::string normalized = "eeeeeaaaaaaiiiiooooouuuuEEEEEAAAAAAIIIIOOOOOUUUU";

    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it == accent.at(0)) {
            str.erase(it, it+1);
        }

        size_t i = 0;
        while (i < accent.size()) {

            if (*it == accent[i+1]) {
                *it = normalized[i/2];
                break;
            }
            i += 2;
        }
    }
    return str;
}

std::string trim(std::string str){

    std::string output = "";

    char c;
    for (unsigned u = 0; u < str.length(); u++) {
        c = str[u];
        if (isalpha(c)) {
            output += toupper(c);
        }
    }
    return output;
}

std::__cxx11::string preprocess(std::__cxx11::string original){

    std::string normalized = "";

    normalized = removeAccent(original);
    normalized = trim(normalized);

    return normalized;
}

std::vector<int> keyToVector(std::string keyString){

    std::vector<int> keyVector;

    for(unsigned u = 0; u < keyString.length(); u++){
        keyVector.push_back(keyString[u]-65);
    }

    return keyVector;
}

std::map<char, int> frequency(std::string str){

    std::map<char, int> chart;

    char ch;
    unsigned cpt;
    unsigned i = 0;

    while(i < str.size()){
        ch = str[i];
        cpt = 0;

        for (auto it = str.cbegin(); it < str.cend(); ++it) {
            if(*it == ch){
                cpt++;
            }
        }
        chart.insert(std::make_pair(ch, cpt));

        i++;
    }
    return chart;
}

double chisqrt(std::string input)
{
    std::map<char, int> freqMap = frequency(input);

    double chiSqrt = 0;

    for (auto itMap = freqMap.cbegin(); itMap != freqMap.cend(); ++itMap){

        auto it = freqFR.cbegin();

        while (it != freqFR.cend() && itMap->first != it->first){
            ++it;
        }

        double var = (((it->second)*input.length())/100)-itMap->second;
        double result = var*var/itMap->second;

        chiSqrt += result;
    }
    return chiSqrt;
}

float IC(std::string str){

    unsigned sizeText = str.length();
    float IC = 0.0;

    std::map<char, int> freqMap = frequency(str);

    for(auto it = freqMap.cbegin(); it != freqMap.cend(); it++){

        float freq = it->second;

        IC += ((float)(freq*(freq-1)/(float)(sizeText*(sizeText-1))));
    }

    return IC;
}

