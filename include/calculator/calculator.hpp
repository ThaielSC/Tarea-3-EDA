#pragma once

#include "IOManager.hpp"
#include "symbol_table.hpp"
#include "parser/tree_builder.hpp"
#include "parser/parser.hpp"
#include "calculator/evaluator.hpp"
#include <iostream>

class Calculator {
private:
  IOManager stream;
  SymbolTable symbols;
  LinkedList* last_postfix_list;
  std::string last_prefix_expr;
  Tree* last_expression_tree;

  void clearLastPostfixList();
  void clearLastExpressionTree();

public:
  Calculator(std::istream &input = std::cin, std::ostream &output = std::cout);
  ~Calculator(); // Add destructor
  void run();

private:
  void loop();
};
