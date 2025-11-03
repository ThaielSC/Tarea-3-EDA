#include "../../include/ADT/node.hpp"
#include <sstream> // Include sstream

Node::Node(double val, NodeType t) 
    : type(t), value(val), next(nullptr), left(nullptr), right(nullptr) {
    
    if (t == OPERAND) {
        std::stringstream ss;
        if (val == static_cast<long long>(val)) {
            ss << static_cast<long long>(val);
        } else {
            ss << val;
        }
        data = ss.str();
    } else {
        data = ""; 
    }
}

Node::Node(const std::string& str, NodeType t) 
    : type(t), data(str), value(0.0), next(nullptr), left(nullptr), right(nullptr) {}