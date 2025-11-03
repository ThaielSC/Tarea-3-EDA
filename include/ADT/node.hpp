#ifndef NODE_HPP
#define NODE_HPP

#include <string>

enum NodeType {
    OPERAND,
    OPERATOR,
    VARIABLE
};

class Node {
public:
    NodeType type;
    std::string data;
    double value;

    // Punteros para LinkedList o Tree
    Node* next;        // LinkedList (siguiente)
    Node* left;        // Usado para Tree (hijo izquierdo)
    Node* right;       // Usado para Tree (hijo derecho)

    // Constructor para int
    Node(double val, NodeType t);

    // Constructor para string
    Node(const std::string& str, NodeType t);

};

#endif