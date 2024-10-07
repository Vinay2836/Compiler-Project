#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "token.h"
#include "symbolTable.h"
#include "reporting.h"
#include "codegen.h"  

class Parser {
public:
    Parser(const std::vector<Token>& tokens, SymbolTable& symTab, Reporting& report, CodeGenerator& codeGen);
    bool parseProgram();
    void endProcedures(); // Declare the endProcedures method
    void endMain();       // Declare the endMain method

private:
    const std::vector<Token>& tokens;
    SymbolTable& symTab;
    Reporting& report;
    CodeGenerator& codeGen; 
    int currentTokenIndex;

    void advanceToken();
    const Token& getCurrentToken();
    void error(const std::string& message);
    void parseDeclarations();
    void parseDeclaration();
    void parseProcedure();
    void parseStatements();
};

#endif 
