#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <vector>
#include <Token.h>
#include <AST.h>
#include <TokenConstants.h>
#include <initializer_list>
#include <algorithm>
#include <Exceptions.h>

using namespace std;
/*
 * expression → equality
 * equality   → comparison ( ( "!=" | "==" ) comparison )*
 * comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )*
 * term       → factor ( ( "-" | "+" ) factor )*
 * factor     → unary ( ( "/" | "*" ) unary )*
 * unary      → ( "!" | "-" ) unary
 *            | primary
 * primary    → NUMBER | STRING | "false" | "true" | "nil"
 *            | "(" expression ")"
*/

namespace JarJar {

   class Parser {
      public:
         Parser(vector<Token> tokens);
         Expression * eval();

      private:
         vector<Token> tokens;
         int pos;

         Expression * equality();
         Expression * comparison();
         Expression * term();
         Expression * factor();
         Expression * unary();
         Expression * primary();
         Expression * grouping();

         bool match(initializer_list<TokenType> types);
         Token advance();
         Token previous();
         TokenType peek();
         bool check(TokenType t);
         bool atEnd();
   };
}


#endif /* SRC_PARSER_H_ */
