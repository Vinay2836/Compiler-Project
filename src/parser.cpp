#include "parser.h"
#include "scanner.h"
#include "symbolTable.h"
#include "reporting.h"
#include <iostream>
#include <vector>
#include <string>

// Helper function to convert TokenType enum to a string
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::PROGRAM_RW: return "PROGRAM_RW";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::IS_RW: return "IS_RW";
        case TokenType::BEGIN_RW: return "BEGIN_RW";
        case TokenType::END_RW: return "END_RW";
        case TokenType::GLOBAL_RW: return "GLOBAL_RW";
        case TokenType::PROCEDURE_RW: return "PROCEDURE_RW";
        case TokenType::VARIABLE_RW: return "VARIABLE_RW";
        case TokenType::COLON: return "COLON";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

// Constructor for the Parser
Parser::Parser(const std::vector<Token>& tokens, SymbolTable& symTab, Reporting& report, CodeGenerator& codeGen)
    : tokens(tokens), symTab(symTab), report(report), codeGen(codeGen), currentTokenIndex(0) {
    // Start generating the main function
    codeGen.generateMainStart();
}

// Main function to parse the program structure
bool Parser::parseProgram() {
    std::cout << "Starting to parse the program..." << std::endl;

    if (getCurrentToken().type == TokenType::PROGRAM_RW) {
        std::cout << "Program Name: " << tokens[currentTokenIndex + 1].value << std::endl; // Show program name
        advanceToken(); // Move past the PROGRAM keyword

        if (getCurrentToken().type == TokenType::IDENTIFIER) {
            std::string programName = getCurrentToken().value;
            symTab.insert(programName, SymbolType::PROGRAM, ""); // Register the program name in symbol table
            advanceToken();

            // Expect the IS keyword after the program name
            if (getCurrentToken().type == TokenType::IS_RW) {
                advanceToken(); // Move past the IS keyword
                parseDeclarations();

                // Expect BEGIN keyword after declarations
                if (getCurrentToken().type == TokenType::BEGIN_RW) {
                    advanceToken(); // Move past the BEGIN keyword
                    parseStatements();

                    // Expect END keyword at the end of the program
                    if (getCurrentToken().type == TokenType::END_RW) {
                        advanceToken(); // Move past the END keyword
                        
                        // End the main function and complete the program
                        codeGen.generateMainEnd();
                        
                        return true; // Program successfully parsed
                    } else {
                        error("Expected 'END' keyword.");
                    }
                } else {
                    error("Expected 'BEGIN' keyword after declarations.");
                }
            } else {
                error("Expected 'IS' keyword after program name.");
            }
        } else {
            error("Expected program name after 'PROGRAM' keyword.");
        }
    } else {
        error("Expected 'PROGRAM' keyword at the beginning of the source file.");
    }

    return false; // Parsing failed
}

// Move to the next token and print the current one for debugging
void Parser::advanceToken() {
    if (currentTokenIndex < static_cast<int>(tokens.size())) {
        std::cout << "Advancing to next token: " << tokens[currentTokenIndex].value
                  << " (Type: " << tokenTypeToString(tokens[currentTokenIndex].type) << ")" << std::endl;
        currentTokenIndex++;
    }
}

// Return the current token
const Token& Parser::getCurrentToken() {
    if (currentTokenIndex < static_cast<int>(tokens.size())) {
        return tokens[currentTokenIndex];
    }
    static Token dummyToken{TokenType::END_OF_FILE, "", 0}; // Dummy token for end of file
    return dummyToken;
}

// Error reporting function with more context
void Parser::error(const std::string& message) {
    std::cerr << "Parse Error: " << message << " at line " << getCurrentToken().line
              << ", token: '" << getCurrentToken().value << " (Type: " << tokenTypeToString(getCurrentToken().type) << ")'" << std::endl;
}

// Parse global and procedure declarations
void Parser::parseDeclarations() {
    std::cout << "Parsing declarations..." << std::endl;
    while (getCurrentToken().type == TokenType::GLOBAL_RW || getCurrentToken().type == TokenType::PROCEDURE_RW) {
        if (getCurrentToken().type == TokenType::GLOBAL_RW) {
            advanceToken();
            parseDeclaration();
        } else if (getCurrentToken().type == TokenType::PROCEDURE_RW) {
            advanceToken();
            parseProcedure();
        }
    }
}

// Parse a single variable declaration
void Parser::parseDeclaration() {
    if (getCurrentToken().type == TokenType::VARIABLE_RW) {
        advanceToken();
        if (getCurrentToken().type == TokenType::IDENTIFIER) {
            std::string varName = getCurrentToken().value;
            advanceToken();

            if (getCurrentToken().type == TokenType::COLON) {
                advanceToken();
                if (getCurrentToken().type == TokenType::IDENTIFIER) {
                    std::string dataType = getCurrentToken().value;
                    advanceToken();
                    symTab.insert(varName, SymbolType::VARIABLE, dataType);
                    
                    // Generate code for the variable declaration
                    codeGen.generateVariableDeclaration(varName, dataType);
                    
                    if (getCurrentToken().type == TokenType::SEMICOLON) {
                        advanceToken();
                    } else {
                        error("Expected ';' after variable declaration.");
                    }
                } else {
                    error("Expected data type after ':'.");
                }
            } else {
                error("Expected ':' after variable name.");
            }
        } else {
            error("Expected variable name after 'VARIABLE' keyword.");
        }
    }
}

// Parse a procedure declaration
void Parser::parseProcedure() {
    if (getCurrentToken().type == TokenType::IDENTIFIER) {
        std::string procName = getCurrentToken().value;
        advanceToken();

        if (getCurrentToken().type == TokenType::COLON) {
            advanceToken();
            if (getCurrentToken().type == TokenType::IDENTIFIER) {
                std::string returnType = getCurrentToken().value;
                advanceToken();
                
                std::string parameters = ""; // Add logic to parse parameters if needed
                // Generate code for the procedure definition
                codeGen.generateProcedureDefinition(procName, returnType, parameters);
            } else {
                error("Expected return type after procedure name.");
            }
        } else {
            error("Expected ':' after procedure name.");
        }
    }
}

// Parse statements
void Parser::parseStatements() {
    while (getCurrentToken().type != TokenType::END_RW && getCurrentToken().type != TokenType::END_OF_FILE) {
        if (getCurrentToken().type == TokenType::IDENTIFIER) {
            std::string varName = getCurrentToken().value;
            advanceToken();

            if (getCurrentToken().type == TokenType::ASSIGN) {
                advanceToken();
                std::string expr = getCurrentToken().value; // This is a placeholder for the expression parsing logic
                advanceToken();
                codeGen.generateAssignment(varName, expr);
            }
        } else if (getCurrentToken().type == TokenType::FOR_RW) {
            advanceToken(); // Move past the FOR keyword
            // Implement the for loop handling here
        } else {
            advanceToken(); // Move to the next token
        }
    }
}
