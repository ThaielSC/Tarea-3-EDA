#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <string>

class Tree {
private:
    Node* root;

    // Funciones auxiliares recursivas para los recorridos
    void deleteRecursive(Node* node);
    void prefixRecursive(Node* node, std::string& output) const;
    void posfixRecursive(Node* node, std::string& output) const;
    
    // Función auxiliar para mostrar el árbol (útil para el comando 'tree')
    void displayRecursive(Node* node, int level) const;

public:
    // Constructor
    Tree();
    // Destructor
    ~Tree();

    void setRoot(Node* newRoot);
    
    Node* getRoot() const;

    std::string getPrefix() const;
    std::string getPosfix() const;
    
    // Mostrar la estructura del árbol (Comando tree)
    void displayTree() const;
};

#endif