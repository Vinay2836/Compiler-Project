#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

// Define the TokenType enumeration
enum class TokenType {
    UNKNOWN,        // Unknown type
    IDENTIFIER,     // Identifier
    KEYWORD,        // Keyword
    NUMBER,         // Number
    STRING,         // String literal
    BOOLEAN,        // Boolean
    PLUS,           // +
    MINUS,          // -
    MULTIPLY,       // *
    DIVIDE,         // /
    ASSIGN,         // :=
    SEMICOLON,      // ;
    COMMA,          // ,
    L_PAREN,        // (
    R_PAREN,        // )
    L_BRACE,        // {
    R_BRACE,        // }
    EOF_TOKEN,      // End of file token
    PROGRAM_RW,     // "program"
    IS_RW,          // "is"
    GLOBAL_RW,      // "global"
    PROCEDURE_RW,   // "procedure"
    BEGIN_RW,       // "begin"
    END_RW,         // "end"
    IF_RW,          // "if"
    THEN_RW,        // "then"
    LOOP_RW,        // "loop"
    END_IF_RW,      // "end if"
    COLON,          // :
    VARIABLE_RW,    // "variable"
    EQUALS,         // "="
    RETURN_RW,      // "return"
    ELSE_RW,        // "else" (for if-else statements)
    FOR_RW,  
    INTEGER,  
    FLOAT_RW,
    BOOL_RW,
    R_BRACKET,
    L_BRACKET,
    END_OF_FILE,
    
         // "for" (for loop structures)
};

// Define the Token class
class Token {
public:
    TokenType type;    // Type of the token
    std::string value; // Value of the token
    int line;          // Line number

    // Default constructor
    Token() : type(TokenType::UNKNOWN), value(""), line(0) {}

    // Constructor with parameters
    Token(TokenType t, const std::string& val, int ln) : type(t), value(val), line(ln) {}

    // Method to print token details
    void printToken() const {
        std::cout << "Token: " << value << ", Type: " << static_cast<int>(type) << ", Line: " << line << std::endl;
    }
};

#endif // TOKEN_H
