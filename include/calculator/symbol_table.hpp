#pragma once

#include "ADT/list.hpp"
#include <string>

class SymbolTable {
private:
    LinkedList table;
    Node* find(const std::string& var_name) const;

public:
    SymbolTable();
    
    bool exists(const std::string& var_name) const;
    double get(const std::string& var_name) const;
    void set(const std::string& var_name, double value);
};
