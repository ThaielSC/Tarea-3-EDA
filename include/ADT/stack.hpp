#ifndef STACK_HPP
#define STACK_HPP

#include "node.hpp"

class Stack {
private:
    Node* top;

public:
    // Constructor
    Stack();
    // Destructor
    ~Stack();

    bool isEmpty() const;

    void push(Node* newNode);

    Node* pop();

    // Retorna Top
    Node* peek() const;
};

#endif