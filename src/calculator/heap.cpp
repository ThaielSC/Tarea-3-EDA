#include "calculator/heap.hpp"
#include <string>

void Heap::addVariable(std::string identifier, double value) {
  bool found = false;
  for (Variable &var : vars) {
    if (var.name == identifier) {
      var.value = value;
      found = true;
      break;
    }
  }
  if (!found) {
    vars.push_back(Variable(identifier, value));
  }
}

bool Heap::hasVariable(const std::string &name) const {
  for (const Variable &var : vars) {
    if (var.name == name) {
      return true;
    }
  }
  return false;
}

double Heap::getVariableValue(const std::string &name) const {
  for (const Variable &var : vars) {
    if (var.name == name) {
      return var.value;
    }
  }
  throw std::runtime_error("Variable '" + name + "' not found.");
}
