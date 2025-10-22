#include "calculator/IOManager.hpp"

IOManager::IOManager(std::istream &input, std::ostream &output)
    : input(input), output(output) {};

void IOManager::read() {
  output << PROMPT;
  getline(input, buffer);
};

void IOManager::write(std::string msg) { output << msg << std::endl; }

std::string IOManager::getBuffer() { return buffer; }
