#include <iostream>
#include "vigenere.h"
#include "caesar.h"
#include "tools.h"

static char ALPHA[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

std::string vigenereCipher(std::string input, std::string key){

    input = preprocess(input);
    key = preprocess(key);
    std::vector<int> keyVector = keyToVector(key);

    std::string output = "";

    int j = 0;
    for(unsigned i = 0; i < input.size(); i++) {

        int index = 0;
        while(index < 26 && input[i] != ALPHA[index]) {
            index++;
        }

        output += ALPHA[(index + keyVector[j]) % 26];
        j = (j + 1) % keyVector.size();
    }
    return output;
}

std::string vigenereDecipher(std::string input, std::string key){

    input = preprocess(input);
    key = preprocess(key);
    std::vector<int> keyVector = keyToVector(key);

    std::string output = "";

    int j = 0;
    for(unsigned i = 0; i < input.size(); i++) {

        int index = 0;
        while(index < 26 && input[i] != ALPHA[index]) {
            index++;
        }

        output += ALPHA[(index - keyVector[j] + 26) % 26];
        j = (j + 1) % keyVector.size();
    }
    return output;
}

std::string vigenereDecipherWithoutKey(std::string input){

    input = preprocess(input);

    int keyLen = keyLength(input);

    if (keyLen == 0){
        throw std::invalid_argument("the input text is too short");
    }

    std::string key = getKey(input, keyLen);

    std::cout << "************************************\n";
    std::cout << "KEY FOUND: " << key << std::endl;
    std::cout << "************************************\n";

    return vigenereDecipher(input, key);
}

int keyLength(std::string str){
    float ICc = 0.0;
    int interval = 0;
    int keyLen = 0;

    while(interval < 15){   //assuming that the length of the key is maximum 15
        interval++;

        std::string subString;
        subString += str[0];    //adding the first letter to the substring

        unsigned index = interval;
        while(index < str.length()){
            subString += str[index];
            index += interval;      //getting the next index depending on the interval
        }

        ICc = IC(subString);

        if (ICc >= 0.07 && ICc < 0.085){
            keyLen = interval;
        }
    }
    return keyLen;
}

std::vector<std::string> partition(std::string str, int keyLen){

    std::vector<std::string> cuts;
    std::string tmp = "";

    unsigned u = 0;
    while (u < str.length()){
        int i = 0;

        while(i < keyLen){
            tmp += str[u+i];
            i++;
        }

        cuts.push_back(tmp);
        tmp = "";
        u += keyLen;

    }
    return cuts;
}

std::string getKey(std::string str, int keyLen){

    std::string key = "";
    std::string tmp = "";

    std::vector<std::string> cuts = partition(str, keyLen);

    for (int i = 0; i < keyLen; i++){

        for(auto it = cuts.cbegin(); it != cuts.cend(); it++){
            tmp += (*it)[i];
        }

        int shift = findShift(tmp);
        key += ALPHA[shift % 26];
        tmp = "";

    }
    return key;
}
