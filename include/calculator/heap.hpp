#include <stdexcept> // For std::runtime_error
#include <string>
#include <vector>

class Variable {
public:
  Variable(std::string name, double value) : name(name), value(value) {}
  std::string name;
  double value;
};

class Heap {
public:
  double ans = 0;

private:
  std::vector<Variable> vars;

public:
  void addVariable(std::string name, double value);
  bool hasVariable(const std::string &name) const;
  double getVariableValue(const std::string &name) const; // Returns double, throws on error
};
