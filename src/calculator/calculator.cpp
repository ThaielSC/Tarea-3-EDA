#include "calculator/calculator.hpp"
#include <iostream>
#include <string>

void Calculator::run() {
    std::cout << "Bienvenido a EdaCal" << std::endl;
    loop();
}

void Calculator::loop() {
    std::string line;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, line);

        if (line == "exit") {
            break;
        }

        // TODO: Process the input line
        // 1. Lexer
        // 2. Parser (to postfix)
        // 3. Evaluate
        // 4. Handle commands (tree, prefix, postfix, show)
        // 5. Store variables

        std::cout << "ans -> [resultado]" << std::endl; // Placeholder
    }
}
