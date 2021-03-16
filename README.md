# CAESAR AND VIGENERE CRYPTANALYSIS

## Project aim

The aim of this project is purely educational. It is meant to show the low security level of an encrypted text using Caesar or Vigenere ciphers.

This tool can:
* encrypt files with a key.
* decrypt files with or without a key.


## Structure of the code

The code is divided in 3 parts: caesar, vigenere and tools.
When running the main function, it will first analyze the given arguments, then preprocess the input text as follow:
* diacritics are removed
* spaces and special characters are removed
* lower case letters are replayced by upper case letters

The result will be written in the given output file that will be created if it doesn't exist yet.


## Technologies

This project is created with C++.


## Setup and run

To download g++ compiler and compile this project, you can run the script:
```
$ ./Setup.sh
```

Or directly compile this project if you already have g++ installed:
```
$ g++ *.cpp -o Main
```

To execute the program, the following options must strictly be in the order as follow:
```
$ ./Main [input] [output] [action] [algorithm] [key]
```
where:
* [input] : the input file
* [output] : the output file
* [action] : -cipher or -decipher
* [algorithm] : -c for Caesar, -v for Vigenere
* [key] : an integer between 1 and 25 if Caesar, a word of maximum 15 letters if Vigenere, 0 if you don't have the key

Examples:
```
$ ./Main Text.txt CiphCaesar.txt -cipher -c 3
$ ./Main  CiphCaesar.txt DeciphCaesar.txt -decipher -c 0

$ ./Main Text.txt CiphVig.txt -cipher -v info
$ ./Main CiphVig.txt DeciphVig.txt -decipher -v 0
```
