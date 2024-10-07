#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <fstream>  
#include "token.h"  

class Scanner {
public:
    // Constructors
    Scanner(const std::string& source);        // For string input
    Scanner(std::ifstream& sourceFile);        // For file input

    std::vector<Token> tokenize();              // Method to tokenize the source code

private:
    std::string source;                         // Source code as string
    size_t currentIndex;                        // Current index in the source
    int currentLine;                            // Current line number

    void skipWhitespace();                       // Method to skip whitespace
    Token createIdentifier();                    // Method to create identifiers
    Token createNumber();                        // Method to create numbers
    Token createSymbol();                        // Method to create symbols

    char peek() const;                          // Peek at the next character
    char getNextChar();                         // Get the next character
};

#endif // SCANNER_H
