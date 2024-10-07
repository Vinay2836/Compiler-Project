#include "symbolTable.h"

void SymbolTable::insert(const std::string& name, SymbolType type, const std::string& dataType) {
    symbols[name] = Symbol{type, dataType};
}

const Symbol* SymbolTable::lookup(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return &it->second;
    }
    return nullptr;
}
