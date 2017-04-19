#include "Token.h"
#include <iostream>

using namespace JarJar;
using namespace std;

namespace JarJar {

    /**
     * Important: order tokens by longest string values to shortest
     * for maximal munch
     */
    vector<pair<TokenType ,string>> Token::typesToString  =
    {
        {TokenType::BREAK, "break"},
        {TokenType::WHILE, "while"},
        {TokenType::IF, "ifsa"},
        {TokenType::ELSE, "elsa"},
        {TokenType::NADA, "nada"},
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

    map<bool, string> Token::boolsToString =
    {
        {true, "ya"},
        {false, "na"}
    };

    int Token::getIntVal()
    {
        return atoi(value.c_str());
    }

    double Token::getDoubleVal()
    {
        return atof(value.c_str());
    }

    string Token::getStringVal()
    {
        return value;
    }

    bool Token::getBoolVal()
    {
        for(pair<bool, string> const &rule : boolsToString)
        {
            if(rule.second == value){
                return rule.first;
            }
        }

        return false; //TODO should not get here, throw exception
    }

    Token::Token(TokenType t,  string v, int l)
    {
        type = t;
        value = v;
        line = l;
    }
}
