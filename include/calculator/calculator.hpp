#pragma once

#include "IOManager.hpp"
#include "heap.hpp"
#include <iostream>

class Calculator {
private:
  IOManager stream;
  Heap variables = Heap();

public:
  Calculator(std::istream &input = std::cin, std::ostream &output = std::cout);
  void run();

private:
  void loop();
};
