#include "calculator/symbol_table.hpp"
#include "ADT/node.hpp"
#include <stdexcept>

SymbolTable::SymbolTable() {}

// Private helper function to find a variable node in the list
Node* SymbolTable::find(const std::string& var_name) const {
    Node* current = table.getHead();
    while (current != nullptr) {
        if (current->type == NodeType::VARIABLE && current->data == var_name) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Not found
}

bool SymbolTable::exists(const std::string& var_name) const {
    return find(var_name) != nullptr;
}

double SymbolTable::get(const std::string& var_name) const {
    Node* var_node = find(var_name);
    if (var_node == nullptr) {
        throw std::runtime_error("Error: Variable '" + var_name + "' no definida.");
    }
    return var_node->value;
}

void SymbolTable::set(const std::string& var_name, double value) {
    Node* var_node = find(var_name);
    if (var_node != nullptr) {
        // Variable exists, update its value
        var_node->value = value;
    } else {
        // Variable doesn't exist, create a new node and add it to the list
        Node* newNode = new Node(var_name, NodeType::VARIABLE);
        newNode->value = value;
        table.append(newNode);
    }
}