#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "node.hpp"

class LinkedList {
private:
    Node* head;
public:
    // Constructor
    LinkedList();
    // Destructor
    ~LinkedList();

    void append(Node* newNode);
    void prepend(Node* newNode); 
    bool isEmpty() const;
    Node* getHead() const;
    void display() const; 
};

#endif