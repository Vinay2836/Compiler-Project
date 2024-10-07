#include "semanticAnalyzer.h"
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer(SymbolTable& symTab) : symTab(symTab) {}

// Function to analyze the tokens and perform semantic checks
bool SemanticAnalyzer::analyze(const std::vector<Token>& tokens) {
    for (const Token& token : tokens) {
        checkDeclaration(token); // Check if variables are declared correctly
        
    }
    return true; // Return true if no errors found
}

// Function to check if a variable is declared
void SemanticAnalyzer::checkDeclaration(const Token& token) {
    if (token.type == TokenType::IDENTIFIER) {
        if (symTab.lookup(token.value) == false) {
            std::cerr << "Error: Undeclared variable '" << token.value << "' at line " << token.line << std::endl;
        }
    }
}

// Function to check type mismatches
void SemanticAnalyzer::checkType(const Token& left, const Token& right, const std::string& operation) {
    
}
