#pragma once

#include "token.hpp"
#include <cstddef>
#include <string>
#include <vector>

class Lexer {
private:
  const std::string *_raw;
  size_t _current_pos;
  std::vector<Token> _tokens;

  bool is_numeric(const char c);
  bool is_alpha(const char c);
  bool is_alphanumeric(const char c);

  void arithmeticOperators();
  void identifier();
  void number();
  char peek();
  char advance();

public:
  Lexer();
  void load(const std::string *raw);
  std::vector<Token> tokenize();
};
