#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <vector>
#include <Token.h>
#include <AST.h>
#include <TokenConstants.h>
#include <initializer_list>
#include <algorithm>
#include <Exceptions.h>
#include <Statement.h>
#include <memory>
#include <algorithm>
#include <typeinfo>

using namespace std;
/*
 * STATEMENTS
 * ==========
 * program         → declaration* EOF
 * declaration     → varDeclaration | statement
 * varDeclaration  → 'var' IDENTIFIER ( '=' expression )? ';' //initializer is optional
 * statement       → exprStatement | ifStatement | printStatement | block | whileStatement | forStatement
 * whileStatement  → 'while' '(' expression ')' statement;
 * forStatement    → 'for' '(' varDeclaration | exprStatement | ':' expression? ';' expression? ')' statement
 * ifStatement     → 'if' '(' expression ')' statement ( 'else' statement )? ;
 * block           → '{' declaration '}'
 * exprStatement   → expression ';'
 * printStatement  → 'print' expression ';'
 * ====================================================================================
 * EXPRESSIONS
 * ===========
 * expression     → assignment
 * assignment     → IDENTIFIER ( '=' assignment )? | logicalOr
 * logicalOr      → logicalAnd ( 'or' logicalAnd )*
 * logicalAnd     → equality ( 'and' logicalAnd )*
 * equality       → comparison ( ( '!=' | '==' ) comparison )*
 * comparison     → term ( ( '>' | '>=' | '<' | '<=' ) term )*
 * term           → factor ( ( '-' | '+' ) factor )*
 * factor         → unary ( ( '/' | '*' ) unary )*
 * unary          → ( '!' | '-' ) unary
 *                | primary
 * primary        → NUMBER | STRING | BOOL | NULL | IDENTIFIER
 *                | '(' expression ')'
*/

namespace JarJar {

   class Parser {
      public:
         Parser(vector<Token> tokens);
         vector<shared_ptr<Statement>>  eval();

      private:
         vector<Token> tokens;
         int pos;

         Statement * declaration();
         Statement * statement();
         Statement * printStatement();
         Statement * ifStatement();
         Statement * expressionStatement();
         Statement * block();
         Statement * whilE();

         Statement* foR();
         Statement* forInitStatement();
         Block* forBody(Expression* postExpression);
         Expression * forExpression(bool consumeEOL = true);


         Expression * assign();
         Expression * expression();
         Expression * logicalOr();
         Expression * logicalAnd();
         Expression * equality();
         Expression * comparison();
         Expression * term();
         Expression * factor();
         Expression * unary();
         Expression * primary();

         bool match(initializer_list<TokenType> types);
         Token advance();
         Token previous();
         TokenType peek();
         bool check(TokenType t);
         bool atEnd();
         void expect(TokenType t);
   };
}


#endif /* SRC_PARSER_H_ */
