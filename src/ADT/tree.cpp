#include "../../include/ADT/tree.hpp"
#include <iostream>

Tree::Tree() : root(nullptr) {}

// Función auxiliar: Recorrido post-orden para liberar la memoria
void Tree::deleteRecursive(Node* node) {
    if (node == nullptr) {
        return;
    }
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete node;
}

// Destructor
Tree::~Tree() {
    deleteRecursive(root);
    root = nullptr;
}

void Tree::setRoot(Node* newRoot) {
    root = newRoot;
}

Node* Tree::getRoot() const {
    return root;
}

void Tree::prefixRecursive(Node* node, std::string& output) const {
    if (node != nullptr) {
        // Raíz
        output += node->data + " "; 
        
        // Izquierda
        prefixRecursive(node->left, output);
        
        // Derecha
        prefixRecursive(node->right, output);
    }
}

std::string Tree::getPrefix() const {
    std::string result = "";
    prefixRecursive(root, result);
    return result;
}


void Tree::posfixRecursive(Node* node, std::string& output) const {
    if (node != nullptr) {
        // Izquierda
        posfixRecursive(node->left, output);
        
        // Derecha
        posfixRecursive(node->right, output);
        
        // Raíz
        output += node->data + " ";
    }
}

std::string Tree::getPosfix() const {
    std::string result = "";
    posfixRecursive(root, result);
    return result;
}

void Tree::displayRecursive(Node* node, int level) const {
    if (node != nullptr) {
        displayRecursive(node->right, level + 1);

        for (int i = 0; i < level; i++) {
            std::cout << "   ";
        }

        std::cout << node->data << std::endl;

        displayRecursive(node->left, level + 1);
    }
}

void Tree::displayTree() const {
    std::cout << "Tree structure (last evaluated expression):" << std::endl;
    displayRecursive(root, 0);
}