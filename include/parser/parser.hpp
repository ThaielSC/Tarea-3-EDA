#ifndef EXPRESSIONCONVERTER_HPP
#define EXPRESSIONCONVERTER_HPP

#include <vector>
#include <string>
#include "lexer/token.hpp"     // Para la entrada (Tokens)
#include "ADT/node.hpp"        // Para la creación de nodos
#include "ADT/stack.hpp"       // Para el algoritmo Shunting-Yard
#include "ADT/list.hpp"  // Para la lista de salida (Posfija)

class ExpressionConverter {
private:
    // Función auxiliar para crear un Nodo a partir de un Token
    Node* createNodeFromToken(const Token& token);
    static int getPrecedence(TokenType token_type);
    static bool isRightAssociative(TokenType token_type);
    
public:
    ExpressionConverter() = default;
    ~ExpressionConverter() = default;

    /**
     * @brief Convierte una lista de Tokens (Infija) a una Lista Enlazada (Posfija).
     * @param tokens La lista de tokens de entrada.
     * @return LinkedList* Un puntero a la nueva lista enlazada en notación Posfija.
     */
    LinkedList* toPostfix(const std::vector<Token>& tokens);
};

#endif // EXPRESSIONCONVERTER_HPP