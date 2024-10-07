#ifndef TYPECHECKER_H
#define TYPECHECKER_H

#include "symbolTable.h"
#include "reporting.h"
#include "token.h" 
#include <vector>
#include <string>

class TypeChecker {
public:
    TypeChecker(SymbolTable& symTab, Reporting& report);

    void checkProgram(const std::vector<Token>& tokens);

private:
    void checkDeclaration(const Token& token);
    void checkAssignment(const std::vector<Token>& tokens, size_t assignIndex);
    void checkIfStatement(const Token& token);
    void checkLoopStatement(const Token& token);

    SymbolTable& symTab;
    Reporting& report;
};

#endif // TYPECHECKER_H
