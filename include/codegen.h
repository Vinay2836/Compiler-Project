#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>

class CodeGenerator {
public:
    CodeGenerator(); // Constructor

    // Function to start and end main function code generation
    void generateMainStart();  // Begin main function
    void generateMainEnd();    // End main function

    // Variable declaration
    void generateVariableDeclaration(const std::string &varName, const std::string &type);

    // Assignment statement
    void generateAssignment(const std::string &varName, const std::string &expr);

    // Procedure definition
    void generateProcedureDefinition(const std::string &procName, const std::string &returnType, const std::string &parameters);
    void endProcedure();  // Close a procedure block

    // For loop generation
    void generateForLoopStart(const std::string &loopVar, const std::string &startVal, const std::string &endVal);
    void endForLoop();  // Close a for loop

    // Code output to file
    void outputCode();

private:
    std::string code;  // Code storage as a string
};

#endif
