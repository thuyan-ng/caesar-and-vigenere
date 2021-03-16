#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>

#include "caesar.h"
#include "vigenere.h"
#include "tools.h"

using namespace std;

string read(ifstream& file);
std::string getVigKey(const char * key);
int getCaesarKey(const char * key);
void write(string output, string text);

int main(int argc, char * argv [])
{
    if (argc < 6){
        cerr << "ERROR: not enough arguments!" << endl;
        exit(1);
    }
    if (argc > 7){
        cerr << "ERROR: too many arguments!" << endl;
        exit(1);
    }

    ifstream fichier(argv[1], ios::in);
    string output(argv[2]);
    bool cipher = strcmp(argv[3], "-cipher")==0;
    bool decipher = strcmp(argv[3], "-decipher")==0;
    bool caesar = strcmp(argv[4], "-c")==0;
    bool vig = strcmp(argv[4], "-v")==0;
    bool noKey = strcmp(argv[5], "0")==0;

    if (fichier){
        string text = read(fichier);

        if (cipher){
            if(noKey){
                cerr << "ERROR: key not found\n";
                exit(1);
            } else {
                if (caesar) {
                    write(output, caesarCipher(text, getCaesarKey(argv[5])));
                } else if (vig) {
                    write(output, vigenereCipher(text, getVigKey(argv[5])));
                } else {
                    cerr << "ERROR: invalid -caesar or -vig invalid. Found option: " << argv[4] << endl;
                    exit(1);
                }
            }

        } else if (decipher){
            if(noKey && caesar){
                write(output, caesarDecipherWithoutKey(text));
            } else if (noKey && vig){
                try {
                write(output, vigenereDecipherWithoutKey(text));
                } catch(const exception & e){
                    cerr << "ERROR: " << e.what() << endl;
                    exit(1);
                }
            } else {
                if (caesar){
                    write(output, caesarDecipher(text, getCaesarKey(argv[5])));
                } else if (vig){
                    write(output, vigenereDecipher(text, getVigKey(argv[5])));
                } else {
                    cerr << "ERROR: invalid -caesar or -vig invalid. Found option: " << argv[4] << endl;
                    exit(1);
                }
            }
        } else {
            cerr << "ERROR: invalid option -cipher or decipher. Found option: " << argv[3] << endl;
            exit(1);
        }
		
		fichier.close();
		
    } else {
        cerr << "ERROR: fail to open file" << endl;
        exit(1);
    }

    return 0;
}

string read(ifstream& file){
    string text = "";
    string line = "";
    while(getline(file, line)){
        text += line;
    }
    cout << "========= INPUT TEXT =========\n" << text << endl;
    return text;
}

std::string getVigKey(const char * key){
    string vigKey(key);
    unsigned i = 0;
    while (i < vigKey.length()){
        if (!isalpha(vigKey[i])){
            cerr << "ERROR: the key must be only letters. Key found: " << key << endl;
            exit(1);
        }
        i++;
    }
    return vigKey;
}

int getCaesarKey(const char * key){
    int caesarKey = atoi(key);
    if(!(caesarKey >= 1 && caesarKey <= 25)){
        cerr << "ERROR: the key must be an integer between 1 and 25. Key found: " << key << endl;
        exit(1);
    }
    return caesarKey;
}

void write(string output, string text){
    cout << "========= OUTPUT TEXT =========\n" << text << endl;
    ofstream file;
    file.open(output, ios::out);
    file << text << "\n";
    file.close();
}

