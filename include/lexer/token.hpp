#pragma once

#include <string>

enum class TokenType {
  // Arithmetic Operators
  PLUS,     // +
  MINUS,    // -
  MULTIPLY, // *
  DIVIDE,   // /
  POWER,    // ^
  SQRT,     // sqrt

  // Assignment
  ASSIGN, // =

  // Grouping
  LPAREN, // (
  RPAREN, // )

  // Literals
  NUMBER,     // e.g., 123, 3.14
  IDENTIFIER, // e.g., ans, x, variable_name

  // Keywords Commands
  SHOW,
  TREE,
  POSFIX,
  PREFIX,
  EXIT,

  // Special Tokens
  EOF_TOKEN, // End of file/input
  UNKNOWN    // For unrecognized tokens
};

struct Token {
  std::string lexema;
  TokenType type;

  Token(TokenType type, const std::string &lexema)
      : lexema(lexema), type(type) {}

  Token(TokenType type) : lexema(""), type(type) {}
};
