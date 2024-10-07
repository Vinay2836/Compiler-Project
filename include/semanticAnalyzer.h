#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "symbolTable.h"
#include "parser.h"
#include <string>
#include <map>

class SemanticAnalyzer {
public:
    SemanticAnalyzer(SymbolTable& symTab);
    bool analyze(const std::vector<Token>& tokens);

private:
    SymbolTable& symTab;
    std::map<std::string, std::string> scope; 
    void checkDeclaration(const Token& token);
    void checkType(const Token& left, const Token& right, const std::string& operation);
};

#endif
