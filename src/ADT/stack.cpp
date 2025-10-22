#include "../../include/ADT/stack.hpp"

Stack::Stack() : top(nullptr) {};

// Destructor
Stack::~Stack() {
    Node* current = top;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
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