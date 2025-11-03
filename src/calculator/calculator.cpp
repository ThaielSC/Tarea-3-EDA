#include "calculator/calculator.hpp"
#include "../../include/lexer/lexer.hpp"
#include "../../include/parser/parser.hpp"
#include "../../include/lexer/token.hpp"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

Calculator::Calculator(std::istream &input, std::ostream &output)
    : stream(IOManager(input, output)), last_postfix_list(nullptr) {}

Calculator::~Calculator() {
    clearLastPostfixList();
}

void Calculator::clearLastPostfixList() {
    if (last_postfix_list != nullptr) {
        delete last_postfix_list;
        last_postfix_list = nullptr;
    }
}

void Calculator::run() {
  stream.write("Bienvenido a EdaCal");
  loop();
}

#include <sstream>
#include <iomanip>

// Helper to format the result, removing trailing zeros for whole numbers
std::string format_result(double value) {
    std::stringstream ss;
    if (value == static_cast<long long>(value)) {
        ss << static_cast<long long>(value);
    } else {
        ss << std::fixed << std::setprecision(6) << value;
        // Trim trailing zeros from decimal part
        std::string s = ss.str();
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        s.erase(s.find_last_not_of('.') + 1, std::string::npos);
        return s;
    }
    return ss.str();
}

void Calculator::loop() {
  Lexer lexer;

  while (true) {
    stream.read(); 

    std::string input_line = stream.getBuffer();
    
    if (input_line == "exit") {
      break; 
    }
    
    if (input_line.empty()) {
        continue;
    }

    lexer.load(&input_line);
    std::vector<Token> tokens = lexer.tokenize();
    
    if (tokens.empty() || tokens[0].type == TokenType::EOF_TOKEN) {
        continue;
    }
    
    // --- LÓGICA DE LA CALCULADORA ---
    
    // Manejar Comandos Especiales
    const Token& first_token = tokens[0];

    if (first_token.type == TokenType::SHOW) {
        stream.write("DEBUG: Comando 'show' detectado. Implementación pendiente.");
        continue;
    } else if (first_token.type == TokenType::TREE) {
        stream.write("DEBUG: Comando 'tree' detectado. Implementación pendiente.");
        continue;
    } else if (first_token.type == TokenType::POSFIX) {
        if (last_postfix_list != nullptr) {
            stream.write("Posfija: " + last_postfix_list->to_string());
        } else {
            stream.write("No hay expresión previa para mostrar en posfija.");
        }
        continue;
    } else if (first_token.type == TokenType::PREFIX) {
        stream.write("DEBUG: Comando 'prefix' detectado. Implementación pendiente.");
        continue;
    } 

    // Pre-procesamiento de tokens para manejar el MENOS UNARIO (-x -> 0-x)
    std::vector<Token> processed_tokens;
    bool is_first_token = true;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        if (token.type == TokenType::MINUS) {
            bool is_unary = false;
            if (is_first_token) {
                is_unary = true;
            } else {
                const auto& prev_token = tokens[i-1];
                if (prev_token.type == TokenType::LPAREN || prev_token.type == TokenType::ASSIGN ||
                    prev_token.type == TokenType::PLUS || prev_token.type == TokenType::MINUS ||
                    prev_token.type == TokenType::MULTIPLY || prev_token.type == TokenType::DIVIDE ||
                    prev_token.type == TokenType::POWER || prev_token.type == TokenType::SQRT) {
                    is_unary = true;
                }
            }
            if (is_unary) {
                processed_tokens.push_back(Token(TokenType::NUMBER, "0"));
            }
        }
        processed_tokens.push_back(token);
        if (token.type != TokenType::EOF_TOKEN) {
            is_first_token = false;
        }
    }
    
    // Lógica de Evaluación de Expresiones
    ExpressionConverter converter;
    TreeBuilder builder;
    Evaluator evaluator(&symbols); // Pasa la tabla de símbolos al evaluador

    LinkedList* postfix_list = nullptr;
    Tree* expression_tree = nullptr;

    try {
        // 1. Convertir a Postfija
        postfix_list = converter.toPostfix(processed_tokens);
        if (!postfix_list) {
            throw std::runtime_error("Error de sintaxis (paréntesis desbalanceados).");
        }
        this->last_postfix_list = postfix_list; // Store the list

        // 2. Construir el Árbol de Expresión (AST)
        expression_tree = builder.buildTree(postfix_list);
        if (!expression_tree) {
            throw std::runtime_error("Error al construir el árbol de expresión.");
        }

        // 3. Evaluar el árbol
        double result = evaluator.evaluate(expression_tree);
        
        // Mostrar el resultado
        stream.write("ans -> " + format_result(result));

    } catch (const std::runtime_error& e) {
        // Capturar y mostrar errores de evaluación o sintaxis
        stream.write(e.what());
    }

    // Limpieza de memoria
    // delete postfix_list; // Removed: last_postfix_list now owns it
    delete expression_tree; // expression_tree is still deleted here
  }
}