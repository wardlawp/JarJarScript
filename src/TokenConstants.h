#ifndef _TOKE_CONSTANTS
#define _TOKE_CONSTANTS

using namespace std;
#include <vector>
#include <map>
#include <exception>

namespace JarJar
{

   enum TokenType
    {
      //Operators
      ASSIGN, EQUALS, NOT_EQUALS, LT, GT, LTE, GTE, ADD, SUB, MUL, DIV, NOT,

      //
      LPAREN, RPAREN, EOL, IDENTIFIER, LBRACKET, RBRACKET,

      //Primitives
      BOOL, INT, DECIMAL, STRING, NADA,

      //Keywords
      AND, OR, IF, ELSE, BREAK, WHILE, FOR, PRINT, VAR
    };

   const string TRUE_REPR = "ya";
   const string FALSE_REPR = "na";
   const char DECIMEL_DOT_REPR = '.';

   /**
     * TODO: This would be better as a map
     * Important: order tokens by longest string values to shortest
     * for maximal munch
     */
    const vector<pair<TokenType ,string>> typesToString  =
    {
      {TokenType::BREAK, "break"},
      {TokenType::WHILE, "while"},
      {TokenType::PRINT, "print"},
      {TokenType::IF, "ifsa"},
      {TokenType::ELSE, "elsa"},
      {TokenType::NADA, "nada"},
      {TokenType::VAR, "var"},
      {TokenType::FOR, "for"},
      {TokenType::AND, "and"},
      {TokenType::OR, "or"},
      {TokenType::BOOL, TRUE_REPR},
      {TokenType::BOOL, FALSE_REPR},
      {TokenType::EQUALS, "=="},
      {TokenType::NOT_EQUALS, "!="},
      {TokenType::LTE, "<="},
      {TokenType::GTE, ">="},
      {TokenType::LPAREN, "("},
      {TokenType::RPAREN, ")"},
      {TokenType::LBRACKET, "{"},
      {TokenType::RBRACKET, "}"},
      {TokenType::EOL, ";"},
      {TokenType::ADD, "+"},
      {TokenType::SUB, "-"},
      {TokenType::LT, "<"},
      {TokenType::GT, ">"},
      {TokenType::MUL, "*"},
      {TokenType::DIV, "/"},
      {TokenType::ASSIGN, "="},
      {TokenType::NOT, "!"}

    };

    const string getStringRepr(const TokenType & t);

    const map<bool, string> boolsToString =
    {
      {true, TRUE_REPR},
      {false, FALSE_REPR}
    };
}

#endif /* _TOKE_CONSTANTS */
