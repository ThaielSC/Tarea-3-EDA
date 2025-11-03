#include "../../include/parser/parser.hpp"
#include <iostream>
#include <cmath>

Node* ExpressionConverter::createNodeFromToken(const Token& token) {
    switch (token.type) {
        case TokenType::NUMBER: {
            double val = std::stod(token.lexema);
            return new Node(val, NodeType::OPERAND);
        }
        case TokenType::IDENTIFIER: {
            return new Node(token.lexema, NodeType::VARIABLE);
        }
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::MULTIPLY:
        case TokenType::DIVIDE:
        case TokenType::POWER:
        case TokenType::SQRT:
        case TokenType::ASSIGN:
            return new Node(token.lexema, NodeType::OPERATOR);
        case TokenType::LPAREN:
        case TokenType::RPAREN:
        default:
            return nullptr;
    }
}

int ExpressionConverter::getPrecedence(TokenType token_type) {
    switch (token_type) {
        case TokenType::ASSIGN:   return 1;
        case TokenType::PLUS:
        case TokenType::MINUS:    return 2;
        case TokenType::MULTIPLY:
        case TokenType::DIVIDE:   return 3;
        case TokenType::POWER:    return 4;
        case TokenType::SQRT:     return 4;
        default:                  return 0;
    }
}

bool ExpressionConverter::isRightAssociative(TokenType token_type) {
    return token_type == TokenType::POWER;
}


// ----------------------------------------------------------------------
// Algoritmo Shunting-Yard (Infija -> Posfija)
// ----------------------------------------------------------------------

LinkedList* ExpressionConverter::toPostfix(const std::vector<Token>& tokens) {
    // 1. Inicializar la lista de salida y la pila de operadores
    LinkedList* output = new LinkedList();
    Stack operatorStack;

    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::NUMBER:
            case TokenType::IDENTIFIER:
                // Si es un operando o variable, se añade inmediatamente a la salida
                output->append(createNodeFromToken(token));
                break;
            
            case TokenType::PLUS:
            case TokenType::MINUS:
            case TokenType::MULTIPLY:
            case TokenType::DIVIDE:
            case TokenType::POWER:
            case TokenType::SQRT:
            case TokenType::ASSIGN:
                // Si es un operador O1
                while (!operatorStack.isEmpty()) {
                    Node* peekNode = operatorStack.peek();
                    if (peekNode == nullptr || peekNode->data == "(") {
                        break; 
                    }
                    // Solo comparamos si el nodo superior es un operador (no '(')
                    if (peekNode->type == NodeType::OPERATOR) {
                        TokenType O2_type = token.type;
                        TokenType O1_type = peekNode->data == "+" ? TokenType::PLUS : 
                                            peekNode->data == "-" ? TokenType::MINUS :
                                            peekNode->data == "*" ? TokenType::MULTIPLY :
                                            peekNode->data == "/" ? TokenType::DIVIDE :
                                            peekNode->data == "^" ? TokenType::POWER :
                                            peekNode->data == "sqrt" ? TokenType::SQRT :
                                            TokenType::UNKNOWN;
                        
                        // Regla de Precedencia y Asociatividad:
                        if (getPrecedence(O1_type) > getPrecedence(O2_type) ||
                            (getPrecedence(O1_type) == getPrecedence(O2_type) && !isRightAssociative(O2_type))) {
                            
                            output->append(operatorStack.pop()); // Mover de pila a salida
                        } else {
                            break; // Se detiene y pushea el nuevo operador
                        }
                    } else {
                        break; // Es un '(' o algo más, se detiene
                    }
                }
                // Push del nuevo operador a la pila
                operatorStack.push(createNodeFromToken(token));
                break;
            
            case TokenType::LPAREN:
                // Si es '(', se pushea a la pila
                operatorStack.push(new Node(std::string("("), NodeType::OPERATOR));
                break;

            case TokenType::RPAREN:
                // Si es ')', se sacan operadores hasta encontrar '('
                while (!operatorStack.isEmpty() && operatorStack.peek()->data != "(") {
                    output->append(operatorStack.pop());
                }
                
                if (operatorStack.isEmpty()) {
                    std::cerr << "Error: Paréntesis desbalanceados (falta '(')." << std::endl;
                    return nullptr; 
                }
                
                // Sacar el '(' de la pila y descartarlo
                delete operatorStack.pop(); 
                break;

            default:
                // Ignorar o manejar error para tokens desconocidos/EOF_TOKEN
                break;
        }
    }

    // 2. Mover los operadores restantes de la pila a la salida
    while (!operatorStack.isEmpty()) {
        Node* op = operatorStack.pop();
        if (op->data == "(") {
             // Error: Paréntesis desbalanceados
            std::cerr << "Error: Paréntesis desbalanceados (falta ')')." << std::endl;
            delete op;
            // Aquí podrías limpiar la memoria y retornar nullptr
            return nullptr;
        }
        output->append(op);
    }
    
    // La lista de salida ahora contiene la expresión en notación Posfija
    return output;
}