#include <iostream>
#include "caesar.h"
#include "tools.h"

static char ALPHA[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

std::string caesarCipher(std::string input, int shift){

    input = preprocess(input);

    std::string output = "";

    for(unsigned i = 0; i < input.size(); i++) {

        int index = 0;
        while (index < 26 && input[i] != ALPHA[index]) {
            index++;
        }

        output += ALPHA[(index + shift + 26) % 26];
    }
    return output;
}

std::string caesarDecipher(std::string input, int shift){

    input = preprocess(input);

    std::string output = "";

    for(unsigned i = 0; i < input.size(); i++){

        int index = 0;
        while(index < 26 && input[i] != ALPHA[index]){
            index++;
        }

        output += ALPHA[(index - shift + 26) % 26];
    }
    return output;
}

std::string caesarDecipherWithoutKey(std::string input){

    input = preprocess(input);

    int shift = findShift(input);

    std::cout << "************************************\n";
    std::cout << "KEY FOUND: " << shift << std::endl;
    std::cout << "************************************\n";

    return caesarDecipher(input, shift);
}

int findShift(std::string str){

    std::vector<std::tuple<int, std::string, double>> brute = bruteShift(str);

    int shift = 0;
    double minChi = std::get<2>(brute[0]);

    for (unsigned i = 0; i < brute.size(); ++i) {

        double chi = std::get<2>(brute[i]);

        if (chi <= minChi) {
            shift = std::get<0>(brute[i]);
            minChi = chi;
        }
    }
    return shift;
}

std::vector<std::tuple<int, std::string, double>> bruteShift(std::string str){

    std::vector<std::tuple<int, std::string, double>> brute;

    for(int u = 0; u < 26; ++u){

        std::string shifted = caesarDecipher(str, u);

        auto tmp = std::make_tuple(u, shifted, chisqrt(shifted));
        brute.push_back(tmp);
    }

    return brute;
}

