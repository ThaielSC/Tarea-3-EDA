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

    // Prevent copies to avoid double-free errors
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void append(Node* newNode);
    void prepend(Node* newNode); 
    bool isEmpty() const;
    Node* getHead() const;
    void display() const; 
    std::string to_string() const;
};

#endif