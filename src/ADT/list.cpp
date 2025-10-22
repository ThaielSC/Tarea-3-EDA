#include "../../include/ADT/list.hpp"
#include <iostream>

LinkedList::LinkedList() : head(nullptr) {}

//Destructor
LinkedList::~LinkedList() {
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

void LinkedList::append(Node* newNode) {
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;

        // Encontrar el último nodo
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::prepend(Node* newNode) {
    newNode->next = head;
    head = newNode;
}

bool LinkedList::isEmpty() const {
    return head == nullptr;
}

Node* LinkedList::getHead() const {
    return head;
}

// ----------------------------------------------------------------------
// display (Opcional, para verificación)
// ----------------------------------------------------------------------
void LinkedList::display() const {
    Node* current = head;
    std::cout << "List: ";
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}