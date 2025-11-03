#include "lexer/lexer.hpp"
#include <cctype>
#include <string>

bool Lexer::is_numeric(const char c) { return c >= '0' && c <= '9'; }

bool Lexer::is_alpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::is_alphanumeric(const char c) {
  return is_alpha(c) || is_numeric(c);
}

Lexer::Lexer() : _raw(nullptr), _current_pos(0) {}

void Lexer::load(const std::string *raw) {
  _raw = raw;
  _current_pos = 0;
}

char Lexer::peek() {
  if (_current_pos >= _raw->length()) {
    return '\0'; // Null character to indicate end of input
  }
  return _raw->at(_current_pos);
}

char Lexer::advance() {
  if (_current_pos >= _raw->length()) {
    return '\0';
  }
  return _raw->at(_current_pos++);
}

void Lexer::number() {
  std::string num_str;
  while (is_numeric(peek())) {
    num_str += advance();
  }
  if (peek() == '.') {
    num_str += advance();
    while (is_numeric(peek())) {
      num_str += advance();
    }
  }
  _tokens.push_back(Token(TokenType::NUMBER, num_str));
}

void Lexer::arithmeticOperators() {
  char c = advance();
  switch (c) {
  case '+':
    _tokens.push_back(Token(TokenType::PLUS, "+"));
    break;
  case '-':
    _tokens.push_back(Token(TokenType::MINUS, "-"));
    break;
  case '*':
    _tokens.push_back(Token(TokenType::MULTIPLY, "*"));
    break;
  case '/':
    _tokens.push_back(Token(TokenType::DIVIDE, "/"));
    break;
  case '^':
    _tokens.push_back(Token(TokenType::POWER, "^"));
    break;
  case '(':
    _tokens.push_back(Token(TokenType::LPAREN, "("));
    break;
  case ')':
    _tokens.push_back(Token(TokenType::RPAREN, ")"));
    break;
  case '=':
    _tokens.push_back(Token(TokenType::ASSIGN, "="));
    break;
  default:
    _tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, c)));
    break;
  }
}

void Lexer::identifier() {
  std::string id_str;
  while (is_alphanumeric(peek())) {
    id_str += advance();
  }

  // Check for keywords
  if (id_str == "show") {
    _tokens.push_back(Token(TokenType::SHOW, id_str));
  } else if (id_str == "tree") {
    _tokens.push_back(Token(TokenType::TREE, id_str));
  } else if (id_str == "posfix") {
    _tokens.push_back(Token(TokenType::POSFIX, id_str));
  } else if (id_str == "prefix") {
    _tokens.push_back(Token(TokenType::PREFIX, id_str));
  } else if (id_str == "exit") {
    _tokens.push_back(Token(TokenType::EXIT, id_str));
  } else if (id_str == "sqrt") {
    _tokens.push_back(Token(TokenType::SQRT, id_str));
  } else {
    _tokens.push_back(Token(TokenType::IDENTIFIER, id_str));
  }
}

std::vector<Token> Lexer::tokenize() {
  _tokens.clear();
  _current_pos = 0;

  while (_current_pos < _raw->length()) {
    char c = peek();

    if (isspace(c)) {
      advance();
      continue;
    }

    if (is_numeric(c)) {
      number();
    } else if (is_alpha(c)) {
      identifier();
    } else {
      arithmeticOperators();
    }
  }

  _tokens.push_back(Token(TokenType::EOF_TOKEN));
  return _tokens;
}
