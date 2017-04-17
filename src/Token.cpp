#include "Token.h"
#include <iostream>

using namespace JarJar;
using namespace std;

namespace JarJar {

    /**
     * Important: order tokens by longest string values to shortest
     * for maximal munch
     */
    vector<pair<TokenType ,string>> Token::typeToString  =
    {
        {TokenType::BREAK, "break"},
        {TokenType::WHILE, "while"},
        {TokenType::IF, "ifsa"},
        {TokenType::ELSE, "elsa"},
        {TokenType::FOR, "for"},
        {TokenType::AND, "and"},
        {TokenType::OR, "or"},
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

    Token::Token(TokenType t, string tx, string v, int l)
    {
        type = t;
        text = tx;
        value = v;
        line = l;
    }
}
