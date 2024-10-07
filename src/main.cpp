#include "scanner.h"
#include "parser.h"
#include "symbolTable.h"
#include "reporting.h"
#include "codegen.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sourcefile>" << std::endl;
        return 1;
    }

    // Open the source file
    std::ifstream sourceFile(argv[1]);
    if (!sourceFile.is_open()) {
        std::cerr << "Error: Could not open source file." << std::endl;
        return 1;
    }

    // Initialize Scanner, SymbolTable, Reporting, and CodeGenerator
    Scanner scanner(sourceFile);
    SymbolTable symTab;
    Reporting report;
    CodeGenerator codeGen;

    // Tokenize the source file
    auto tokens = scanner.tokenize();

    // Initialize the Parser and parse the program
    Parser parser(tokens, symTab, report, codeGen);
    if (parser.parseProgram()) {
        std::cout << "Parsing successful!" << std::endl;
        codeGen.outputCode();  // Output the generated code
    } else {
        std::cerr << "Parsing failed." << std::endl;
    }

    return 0;
}
