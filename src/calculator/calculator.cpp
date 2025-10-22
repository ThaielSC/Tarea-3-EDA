#include "calculator/calculator.hpp"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

void Calculator::run() {
  stream.write("Bienvenido a EdaCal");
  loop();
}

void Calculator::loop() {
  while (true) {
    stream.read();
    stream.write(stream.getBuffer());
  }
}

Calculator::Calculator(std::istream &input, std::ostream &output)
    : stream(IOManager(input, output)) {}
