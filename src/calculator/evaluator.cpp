#include "calculator/evaluator.hpp"
#include <cmath>
#include <stdexcept>

Evaluator::Evaluator(SymbolTable* symbol_table) : symbols(symbol_table) {}

double Evaluator::evaluate(Tree* tree) {
    if (!tree || !tree->getRoot()) {
        throw std::runtime_error("Error: No se puede evaluar un árbol vacío.");
    }
    return evaluateRecursive(tree->getRoot());
}

double Evaluator::evaluateRecursive(Node* node) {
    if (!node) {
        throw std::runtime_error("Error: Nodo inválido en el árbol de expresión.");
    }

    switch (node->type) {
        case NodeType::OPERAND:
            return node->value;

        case NodeType::VARIABLE:
            return symbols->get(node->data);

        case NodeType::OPERATOR: {
            if (node->data == "=") {
                if (!node->left || node->left->type != NodeType::VARIABLE) {
                    throw std::runtime_error("Error: La asignación debe tener una variable a la izquierda.");
                }
                double value = evaluateRecursive(node->right);
                symbols->set(node->left->data, value);
                return value;
            }

            // Para los demás operadores, primero evaluamos el/los hijo(s)
            double left_val = evaluateRecursive(node->left);

            if (node->data == "sqrt") { // Operador Unario
                return std::sqrt(left_val);
            }

            double right_val = evaluateRecursive(node->right);

            if (node->data == "+") return left_val + right_val;
            if (node->data == "-") return left_val - right_val;
            if (node->data == "*") return left_val * right_val;
            if (node->data == "/") {
                if (right_val == 0) throw std::runtime_error("Error: División por cero.");
                return left_val / right_val;
            }
            if (node->data == "^") return std::pow(left_val, right_val);
            
            throw std::runtime_error("Error: Operador desconocido '" + node->data + "'.");
        }
        default:
            throw std::runtime_error("Error: Tipo de nodo desconocido.");
    }
}
