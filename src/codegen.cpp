#include "codegen.h"
#include <iostream>
#include <fstream>

// Constructor: Initialize the code with standard C++ includes and namespace
CodeGenerator::CodeGenerator() {
    code = "#include <iostream>\n";
    code += "using namespace std;\n\n";
}

// Start the main function
void CodeGenerator::generateMainStart() {
    code += "int main() {\n";  // Start the main function
}

// End the main function
void CodeGenerator::generateMainEnd() {
    code += "    return 0;\n"; // Return statement at the end of main
    code += "}\n"; // Close the main function
}

// Generate a variable declaration based on the type
void CodeGenerator::generateVariableDeclaration(const std::string &varName, const std::string &type) {
    if (type == "integer") {
        code += "    int " + varName + ";\n";
    } else if (type == "float") {
        code += "    float " + varName + ";\n";
    } else if (type == "bool") {
        code += "    bool " + varName + ";\n";
    } else {
        code += "    " + type + " " + varName + ";\n";  // Handle other data types generically
    }
}

// Generate a procedure definition
void CodeGenerator::generateProcedureDefinition(const std::string &procName, const std::string &returnType, const std::string &parameters) {
    code += returnType + " " + procName + "(" + parameters + ") {\n";
}

// Close a procedure definition
void CodeGenerator::endProcedure() {
    code += "}\n\n";  // Close the procedure block
}

// Generate an assignment statement
void CodeGenerator::generateAssignment(const std::string &varName, const std::string &expr) {
    code += "    " + varName + " = " + expr + ";\n";
}

// Generate a `for` loop construct
void CodeGenerator::generateForLoopStart(const std::string &loopVar, const std::string &startVal, const std::string &endVal) {
    code += "    for (" + loopVar + " = " + startVal + "; " + loopVar + " <= " + endVal + "; " + loopVar + "++) {\n";
}

// End a loop construct
void CodeGenerator::endForLoop() {
    code += "    }\n";
}

// Method to output the generated code to a file named 'output.cpp'
void CodeGenerator::outputCode() {
    std::ofstream outFile("output.cpp");
    if (outFile.is_open()) {
        outFile << code;
        outFile.close();
        std::cout << "Generated code written to output.cpp" << std::endl;
    } else {
        std::cerr << "Error: Could not open output file for writing." << std::endl;
    }
}
