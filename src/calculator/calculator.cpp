#include "calculator/calculator.hpp"
#include "../../include/lexer/lexer.hpp"
#include "../../include/parser/parser.hpp"
#include "../../include/lexer/token.hpp"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

Calculator::Calculator(std::istream &input, std::ostream &output)
    : stream(IOManager(input, output)) {}

void Calculator::run() {
  stream.write("Bienvenido a EdaCal");
  loop();
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
        stream.write("DEBUG: Comando 'posfix' detectado. Implementación pendiente.");
        continue;
    } else if (first_token.type == TokenType::PREFIX) {
        stream.write("DEBUG: Comando 'prefix' detectado. Implementación pendiente.");
        continue;
    } 
    
    // Lógica de Evaluación de Expresiones
    // Convertir a Posfija
    ExpressionConverter converter;
    LinkedList* postfix_list = converter.toPostfix(tokens);

    if (postfix_list != nullptr) {

        //DEBUGER POSFIJA
        stream.write("DEBUG: Posfija: " + postfix_list->to_string());
        
        // Próximo paso: construir el Árbol de Expresión y Evaluar
        
        delete postfix_list; 
    } else {
        stream.write("Error en la sintaxis de la expresión. Evaluación cancelada.");
    }
  }
}