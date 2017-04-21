#include <vector>
#include <map>

using namespace std;

#ifndef _TOKE_CONSTANTS
#define _TOKE_CONSTANTS

namespace JarJar
{

   enum TokenType
    {
      //Operators
      ASSIGN, EQUALS, NOT_EQUALS, LT, GT, LTE, GTE, ADD, SUB, MUL, DIV, NEGATE,
      LPAREN, RPAREN,

      //Primitives
      BOOL, INT, DECIMAL, STRING, NADA,

      //Keywords
      AND, OR, IF, ELSE, BREAK, WHILE, FOR
    };

   const string TRUE_REPR = "ya";
   const string FALSE_REPR = "na";
   const char DECIMEL_DOT_REPR = '.';

   /**
     * Important: order tokens by longest string values to shortest
     * for maximal munch
     */
    const vector<pair<TokenType ,string>> typesToString  =
    {
      {TokenType::BREAK, "break"},
      {TokenType::WHILE, "while"},
      {TokenType::IF, "ifsa"},
      {TokenType::ELSE, "elsa"},
      {TokenType::NADA, "nada"},
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
      {TokenType::ADD, "+"},
      {TokenType::SUB, "-"},
      {TokenType::LT, "<"},
      {TokenType::GT, ">"},
      {TokenType::MUL, "*"},
      {TokenType::DIV, "/"},
      {TokenType::ASSIGN, "="},
      {TokenType::NEGATE, "!"}

    };

    const map<bool, string> boolsToString =
    {
      {true, TRUE_REPR},
      {false, FALSE_REPR}
    };
}

#endif
