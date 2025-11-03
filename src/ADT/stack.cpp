#include "../../include/ADT/stack.hpp"

Stack::Stack() : top(nullptr) {};

// Destructor
Stack::~Stack() {
    // Los nodos son gestionados por otras estructuras (LinkedList, Tree).
    // El destructor de la pila no debe liberar esta memoria para evitar doble liberación.
    top = nullptr;
}

bool Stack::isEmpty() const{
    return top == nullptr;
}

void Stack::push(Node* newNode) {
    newNode->next = top;
    top = newNode;
}

Node* Stack::pop() {
    if (isEmpty()){
        return nullptr;
    }
    Node* temp = top;
    top = top-> next;
    temp -> next = nullptr;
    return temp;
}

Node* Stack::peek() const{
    return top;
}