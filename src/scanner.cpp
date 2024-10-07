#include "scanner.h"
#include <cctype>
#include <iostream>

// Constructor for string input
Scanner::Scanner(const std::string& source)
    : source(source), currentIndex(0), currentLine(1) {}

// Constructor for file input
Scanner::Scanner(std::ifstream& sourceFile) {
    std::string line;
    while (std::getline(sourceFile, line)) {
        source += line + '\n'; 
    }
    currentIndex = 0; // Initialize current index
    currentLine = 1;  // Initialize line number
}

// Function to tokenize the source code
std::vector<Token> Scanner::tokenize() {
    std::vector<Token> tokens;
    while (currentIndex < source.length()) {
        char currentChar = peek();
        if (isspace(currentChar)) {
            skipWhitespace();
        } else if (isalpha(currentChar)) {
            tokens.push_back(createIdentifier());
        } else if (isdigit(currentChar)) {
            tokens.push_back(createNumber());
        } else {
            tokens.push_back(createSymbol());
        }
    }
    tokens.push_back({TokenType::END_OF_FILE, "", currentLine});
    return tokens;
}

// Skip whitespace
void Scanner::skipWhitespace() {
    while (currentIndex < source.length() && isspace(peek())) {
        if (peek() == '\n') currentLine++;
        getNextChar();
    }
}


// Create identifiers and keywords
Token Scanner::createIdentifier() {
    std::string value;
    while (currentIndex < source.length() && (isalnum(peek()) || peek() == '_')) {
        value += getNextChar();
    }

    std::cout << "Identified token: " << value << std::endl;  

    // Determine if it is a keyword or identifier
    if (value == "program") return {TokenType::PROGRAM_RW, value, currentLine};
    if (value == "is") return {TokenType::IS_RW, value, currentLine};  // Ensure this line exists
    if (value == "begin") return {TokenType::BEGIN_RW, value, currentLine};
    if (value == "end") return {TokenType::END_RW, value, currentLine};
    if (value == "global") return {TokenType::GLOBAL_RW, value, currentLine};
    if (value == "variable") return {TokenType::VARIABLE_RW, value, currentLine};
    if (value == "procedure") return {TokenType::PROCEDURE_RW, value, currentLine};
    if (value == "INDENTIFIER") return{TokenType::IDENTIFIER,value,currentLine};
    // Add other keywords as necessary...

    return {TokenType::IDENTIFIER, value, currentLine};
}


// Create numbers
Token Scanner::createNumber() {
    std::string value;
    while (currentIndex < source.length() && isdigit(peek())) {
        value += getNextChar();
    }
    return {TokenType::INTEGER, value, currentLine};
}

// Handle symbols and operators
Token Scanner::createSymbol() {
    char symbol = getNextChar(); // Get the current symbol
    // Here you could expand this section to handle different symbols/operators
    switch (symbol) {
        case ';': return {TokenType::SEMICOLON, std::string(1, symbol), currentLine};
        case ':': return {TokenType::COLON, std::string(1, symbol), currentLine};
        case '=': return {TokenType::ASSIGN, std::string(1, symbol), currentLine};
        // Add cases for other symbols...
        default: return {TokenType::UNKNOWN, std::string(1, symbol), currentLine};
    }
}

// Peek at the next character without consuming it
char Scanner::peek() const {
    if (currentIndex < source.length()) {
        return source[currentIndex];
    }
    return '\0'; // End of string
}

// Get the next character and advance the index
char Scanner::getNextChar() {
    if (currentIndex < source.length()) {
        return source[currentIndex++];
    }
    return '\0'; // End of string
}
