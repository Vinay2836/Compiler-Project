#include "reporting.h"
#include <iostream>

void Reporting::reportError(const std::string& message, int line) {
    errors.push_back("Error on line " + std::to_string(line) + ": " + message);
}

void Reporting::printErrors() const {
    for (const auto& error : errors) {
        std::cerr << error << std::endl;
    }
}
