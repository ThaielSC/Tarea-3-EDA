#include "../../include/ADT/node.hpp"

Node::Node(double val, NodeType t) 
    : type(t), value(val), next(nullptr), left(nullptr), right(nullptr) {
    
    if (t == OPERAND) {
        data = std::to_string(val); 
    } else {
        data = ""; 
    }
}

Node::Node(const std::string& str, NodeType t) 
    : type(t), data(str), value(0.0), next(nullptr), left(nullptr), right(nullptr) {}