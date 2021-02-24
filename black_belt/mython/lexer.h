#pragma once

#include <iosfwd>
#include <string>
#include <sstream>
#include <variant>
#include <stdexcept>
#include <optional>
#include <unordered_map>

class TestRunner;

namespace Parse {

  namespace TokenType {
    struct Number {
      int value;
    };

    struct Id {
      std::string value;
    };

    struct Char {
      char value;
    };

    struct String {
      std::string value;
    };

    struct Class {};
    struct Return {};
    struct If {};
    struct Else {};
    struct Def {};
    struct Newline {};
    struct Print {};
    struct Indent {};
    struct Dedent {};
    struct Eof {};
    struct And {};
    struct Or {};
    struct Not {};
    struct Eq {};
    struct NotEq {};
    struct LessOrEq {};
    struct GreaterOrEq {};
    struct None {};
    struct True {};
    struct False {};
  }

  using TokenBase = std::variant <
    TokenType::Number,
    TokenType::Id,
    TokenType::Char,
    TokenType::String,
    TokenType::Class,
    TokenType::Return,
    TokenType::If,
    TokenType::Else,
    TokenType::Def,
    TokenType::Newline,
    TokenType::Print,
    TokenType::Indent,
    TokenType::Dedent,
    TokenType::And,
    TokenType::Or,
    TokenType::Not,
    TokenType::Eq,
    TokenType::NotEq,
    TokenType::LessOrEq,
    TokenType::GreaterOrEq,
    TokenType::None,
    TokenType::True,
    TokenType::False,
    TokenType::Eof
  > ;


  //По сравнению с условием задачи мы добавили в тип Token несколько
  //удобных методов, которые делают код короче. Например,
  //
  //token.Is<TokenType::Id>()
  //
  //гораздо короче, чем
  //
  //std::holds_alternative<TokenType::Id>(token).
  struct Token : TokenBase {
    using TokenBase::TokenBase;

    template <typename T>
    bool Is() const {
      return std::holds_alternative<T>(*this);
    }

    template <typename T>
    const T& As() const {
      return std::get<T>(*this);
    }

    template <typename T>
    const T* TryAs() const {
      return std::get_if<T>(this);
    }
  };

  bool operator == (const Token& lhs, const Token& rhs);
  std::ostream& operator << (std::ostream& os, const Token& rhs);

  class LexerError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };

  class Lexer {
  public:
    explicit Lexer(std::istream& input);

    const Token& CurrentToken() const;
    Token NextToken();

    template <typename T>
    const T& Expect() const {
      if (!current_token.Is<T>()) {
        throw LexerError("");
      }
      else return *current_token.TryAs<T>();
    }

    template <typename T, typename U>
    void Expect(const U& value) const {
      if (!(current_token.Is<T>() && current_token.TryAs<T>()->value == value)) {
        throw LexerError("");
      }
    }

    template <typename T>
    const T& ExpectNext() {
      NextToken();
      return Expect<T>();
    }

    template <typename T, typename U>
    void ExpectNext(const U& value) {
      NextToken();
      Expect<T>(value);
    }
  private:
    void SkipEmptyLines();
    std::optional<Token> ControlIndent();
    std::optional<Token> TryNumber();
    std::optional<Token> TryAnyId();
    std::optional<Token> TryChar();
    std::optional<Token> TryString();
    std::optional<Token> TryEof();
  private:
    const std::unordered_map<std::string, Token> translator = {
      {"class", TokenType::Class{}},
      {"return", TokenType::Return{}},
      {"if", TokenType::If{}},
      {"else", TokenType::Else{}},
      {"def", TokenType::Def{}},
      {"print", TokenType::Print{}},
      {"and", TokenType::And{}},
      {"or", TokenType::Or{}},
      {"not", TokenType::Not{}},
      {"None", TokenType::None{}},
      {"True", TokenType::True{}},
      {"False", TokenType::False{}}
    };
  private:
    std::istream& input;
    Token current_token;
    unsigned indent = 0;
    unsigned unreturned_dif = 0;
  };

  void RunLexerTests(TestRunner& test_runner);
  bool IsNumber(char c);
  bool IdChar(char c);
  void SkipSpaces(std::istream& in);

} /* namespace Parse */
