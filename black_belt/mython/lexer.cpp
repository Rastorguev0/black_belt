#include "lexer.h"

#include <algorithm>
#include <charconv>

using namespace std;

namespace Parse {

  bool operator == (const Token& lhs, const Token& rhs) {
    using namespace TokenType;

    if (lhs.index() != rhs.index()) {
      return false;
    }
    if (lhs.Is<Char>()) {
      return lhs.As<Char>().value == rhs.As<Char>().value;
    }
    else if (lhs.Is<Number>()) {
      return lhs.As<Number>().value == rhs.As<Number>().value;
    }
    else if (lhs.Is<String>()) {
      return lhs.As<String>().value == rhs.As<String>().value;
    }
    else if (lhs.Is<Id>()) {
      return lhs.As<Id>().value == rhs.As<Id>().value;
    }
    else {
      return true;
    }
  }

  ostream& operator << (ostream& os, const Token& rhs) {
    using namespace TokenType;

#define VALUED_OUTPUT(type) \
  if (auto p = rhs.TryAs<type>()) return os << #type << '{' << p->value << '}';

    VALUED_OUTPUT(Number);
    VALUED_OUTPUT(Id);
    VALUED_OUTPUT(String);
    VALUED_OUTPUT(Char);

#undef VALUED_OUTPUT

#define UNVALUED_OUTPUT(type) \
    if (rhs.Is<type>()) return os << #type;

    UNVALUED_OUTPUT(Class);
    UNVALUED_OUTPUT(Return);
    UNVALUED_OUTPUT(If);
    UNVALUED_OUTPUT(Else);
    UNVALUED_OUTPUT(Def);
    UNVALUED_OUTPUT(Newline);
    UNVALUED_OUTPUT(Print);
    UNVALUED_OUTPUT(Indent);
    UNVALUED_OUTPUT(Dedent);
    UNVALUED_OUTPUT(And);
    UNVALUED_OUTPUT(Or);
    UNVALUED_OUTPUT(Not);
    UNVALUED_OUTPUT(Eq);
    UNVALUED_OUTPUT(NotEq);
    UNVALUED_OUTPUT(LessOrEq);
    UNVALUED_OUTPUT(GreaterOrEq);
    UNVALUED_OUTPUT(None);
    UNVALUED_OUTPUT(True);
    UNVALUED_OUTPUT(False);
    UNVALUED_OUTPUT(Eof);

#undef UNVALUED_OUTPUT

    return os << "Unknown token :(";
  }


  Lexer::Lexer(istream& input) : input(input) {
    while (input.peek() == '\n') {
      input.ignore(1);
    }
    NextToken();
  }

  const Token& Lexer::CurrentToken() const {
    return current_token;
  }

  Token Lexer::NextToken() {
    optional<Token> token = TryEof();

    SkipEmptyLines();
    if (!token) {
      token = ControlIndent();
    }
    SkipSpaces(input);

    if (!token) {
      token = TryNumber();
    }
    if (!token) {
      token = TryAnyId();
    }
    if (!token) {
      token = TryString();
    }
    if (!token) {
      token = TryChar();
    }
    current_token = token.value();
    return current_token;
  }

  optional<Token> Lexer::ControlIndent() {
    if (unreturned_dif > 0) {
      unreturned_dif--;
      if (current_token.Is<TokenType::Indent>()) indent++;
      else indent--;
      return current_token;
    }
    if (!current_token.Is<TokenType::Newline>()) return nullopt;
    char space;
    unsigned cur_indent = 0;
    for (int i = 0; input.get(space); ++i) {
      if (space == ' ') {
        cur_indent += i % 2;
      }
      else {
        input.putback(space);
        break;
      }
    }
    unreturned_dif = max(cur_indent, indent) - min(cur_indent, indent);
    if (cur_indent > indent) {
      unreturned_dif--;
      indent++;
      return TokenType::Indent{};
    }
    else if (cur_indent < indent) {
      indent--;
      unreturned_dif--;
      return TokenType::Dedent{};
    }
    else return nullopt;
  }

  optional<Token> Lexer::TryNumber() {
    if (IsNumber(input.peek())) {
      int n;
      input >> n;
      return TokenType::Number{ n };
    }
    else return nullopt;
  }

  optional<Token> Lexer::TryAnyId() {
    string id;
    char another;
    while (input.get(another) && IdChar(another)) {
      id.push_back(another);
    }
    if (input) input.putback(another);
    if (translator.count(id)) return translator.at(id);
    else if (!id.empty()) return TokenType::Id{ id };
    else return nullopt;
  }


  optional<Token> Lexer::TryString() {
    string str;
    char quote = input.get();
    if (quote == '\'' || quote == '\"') {
      getline(input, str, quote);
      return TokenType::String{ str };
    }
    else input.putback(quote);
    return nullopt;
  }


  optional<Token> Lexer::TryChar() {
    char c = input.get();
    if (c == '\n') return TokenType::Newline{};
    else if (c == '!' && input.peek() == '=') {
      input.ignore(1);
      return TokenType::NotEq{};
    }
    else if (c == '<' && input.peek() == '=') {
      input.ignore(1);
      return TokenType::LessOrEq{};
    }
    else if (c == '>' && input.peek() == '=') {
      input.ignore(1);
      return TokenType::GreaterOrEq{};
    }
    else if (c == '=' && input.peek() == '=') {
      input.ignore(1);
      return TokenType::Eq{};
    }
    return TokenType::Char{ c };
  }

  optional<Token> Lexer::TryEof() {
    if (current_token.Is<TokenType::Eof>()) return current_token;
    if (char _;  input && input.get(_)) {
      input.putback(_);
      return nullopt;
    }
    else {
      if (!current_token.Is<TokenType::Newline>() && !current_token.Is<TokenType::Dedent>()) {
        return TokenType::Newline{};
      }
      else {
        if (indent > 0) {
          indent--;
          return TokenType::Dedent{};
        }
        else return TokenType::Eof{};
      }
    }
  }



  bool IsNumber(char c) {
    return ('0' <= c && c <= '9');
  }

  bool IdChar(char c) {
    return ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || c == '_' || IsNumber(c));
  }

  void SkipSpaces(istream& input) {
    while (input.peek() == ' ') {
      input.ignore(1);
    }
  }

  void Lexer::SkipEmptyLines() {
    while (current_token.Is<TokenType::Newline>() && input.peek() == '\n') {
      input.ignore(1);
    }
  }

} /* namespace Parse */
