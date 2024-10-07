#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>

enum class SymbolType {
    PROGRAM,    
    VARIABLE,
    PROCEDURE
};

struct Symbol {
    SymbolType type;
    std::string dataType;
};

class SymbolTable {
public:
    void insert(const std::string& name, SymbolType type, const std::string& dataType);
    const Symbol* lookup(const std::string& name) const;

private:
    std::unordered_map<std::string, Symbol> symbols;
};

#endif  // SYMBOLTABLE_H
