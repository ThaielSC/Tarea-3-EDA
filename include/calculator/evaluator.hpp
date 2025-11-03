#pragma once

#include "ADT/tree.hpp"
#include "calculator/symbol_table.hpp"

class Evaluator {
private:
    SymbolTable* symbols;
    double evaluateRecursive(Node* node);

public:
    Evaluator(SymbolTable* symbol_table);
    double evaluate(Tree* tree);
};
