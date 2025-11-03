#include "parser/tree_builder.hpp"
#include "ADT/stack.hpp"
#include <stdexcept>

// Helper to recursively delete a node and its children
void delete_node_recursive(Node* node) {
    if (node == nullptr) {
        return;
    }
    delete_node_recursive(node->left);
    delete_node_recursive(node->right);
    delete node;
}

Tree* TreeBuilder::buildTree(const LinkedList* postfix_list) {
    if (!postfix_list || postfix_list->isEmpty()) {
        return nullptr;
    }

    Stack nodeStack;
    Node* current = postfix_list->getHead();

    try {
        while (current != nullptr) {
            Node* newNode = new Node(*current);

            if (newNode->type == NodeType::OPERAND || newNode->type == NodeType::VARIABLE) {
                nodeStack.push(newNode);
            } else if (newNode->type == NodeType::OPERATOR) {
                Node* right = nullptr;
                Node* left = nullptr;

                if (newNode->data == "sqrt") { // Unary operator
                    if (nodeStack.isEmpty()) {
                        delete newNode;
                        throw std::runtime_error("Error de sintaxis: Faltan operandos para 'sqrt'.");
                    }
                    right = nodeStack.pop();
                    newNode->left = right;
                } else { // Binary operator
                    if (nodeStack.isEmpty()) {
                        delete newNode;
                        throw std::runtime_error("Error de sintaxis: Faltan operandos para el operador.");
                    }
                    right = nodeStack.pop();

                    if (nodeStack.isEmpty()) {
                        nodeStack.push(right); // Push back for cleanup
                        delete newNode;
                        throw std::runtime_error("Error de sintaxis: Faltan operandos para el operador.");
                    }
                    left = nodeStack.pop();

                    newNode->left = left;
                    newNode->right = right;
                }
                nodeStack.push(newNode);
            }
            current = current->next;
        }

        Node* rootNode = nodeStack.pop();

        if (!nodeStack.isEmpty()) {
            nodeStack.push(rootNode); // Push back for cleanup
            throw std::runtime_error("Error de sintaxis: Demasiados operandos en la expresión.");
        }

        Tree* tree = new Tree();
        tree->setRoot(rootNode);
        return tree;

    } catch (...) {
        // Centralized cleanup: clean the entire stack on any error.
        while (!nodeStack.isEmpty()) {
            delete_node_recursive(nodeStack.pop());
        }
        throw; // Re-throw the caught exception to be handled by the calculator loop.
    }
}
