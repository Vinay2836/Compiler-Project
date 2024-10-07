#include "typechecker.h"

TypeChecker::TypeChecker(SymbolTable& symTab, Reporting& report)
    : symTab(symTab), report(report) {}

void TypeChecker::checkProgram(const std::vector<Token>& tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];

        if (token.type == TokenType::IDENTIFIER) {
            // Check variable declarations
            checkDeclaration(token);
        } else if (token.type == TokenType::ASSIGN) {
            // Check assignments
            checkAssignment(tokens, i);
        } else if (token.type == TokenType::IF_RW) {
            // Check if statements
            checkIfStatement(token);
        } else if (token.type == TokenType::LOOP_RW) {
            // Check loop statements
            checkLoopStatement(token);
        }
    }
}

void TypeChecker::checkDeclaration(const Token& token) {
    std::string varName = token.value;

    // Ignore keywords and types
    if (token.type == TokenType::PROGRAM_RW || 
        token.type == TokenType::GLOBAL_RW ||
        token.type == TokenType::VARIABLE_RW ||
        token.type == TokenType::INTEGER_RW || 
        token.type == TokenType::FLOAT_RW ||
        token.type == TokenType::BOOL_RW) {
        return; 
    }

    
    if (symTab.lookup(varName)) {
        report.reportError("Variable '" + varName + "' is already declared", token.line);
    } else {
        // Add the variable to the symbol table with its type (assuming it's INTEGER for now)
        symTab.insert(varName, SymbolType::VARIABLE, "INTEGER"); // Adjust type accordingly
    }
}

void TypeChecker::checkAssignment(const std::vector<Token>& tokens, size_t assignIndex) {
    if (assignIndex == 0 || tokens[assignIndex - 1].type != TokenType::IDENTIFIER) {
        report.reportError("Invalid assignment, left-hand side variable is missing", tokens[assignIndex].line);
        return;
    }

    std::string varName = tokens[assignIndex - 1].value;

    // Check if the variable is declared
    if (!symTab.lookup(varName)) {
        report.reportError("Variable '" + varName + "' is not declared", tokens[assignIndex].line);
    }
}

void TypeChecker::checkIfStatement(const Token& token) {
    // Implement logic for if statements
}

void TypeChecker::checkLoopStatement(const Token& token) {
    // Implement logic for loop statements
}
