#include <Parser.h>

namespace JarJar {

   Parser::Parser(vector<Token> tokens)
   {
      this->tokens = tokens;
      pos = 0;
   }

   Expression * Parser::eval()
   {
      return equality();
   }

   Expression * Parser::equality()
   {
      Expression * lhs = comparison();

      if(match({TokenType::EQUALS, TokenType::NOT_EQUALS}))
      {
         return new Binary(lhs, previous(), comparison());
      }

      return lhs;
   }

   Expression * Parser::comparison()
   {
      Expression * lhs = term();

      if(match({TokenType::LT, TokenType::LTE, TokenType::GT, TokenType::GTE}))
      {
         return new Binary(lhs, previous(), term());
      }

      return lhs;
   }

   Expression * Parser::term()
   {
      Expression * lhs = factor();

      if(match({TokenType::ADD, TokenType::SUB}))
      {
         return new Binary(lhs, previous(), factor());
      }

      return lhs;
   }

   Expression * Parser::factor()
   {
      Expression * lhs = unary();

      if(match({TokenType::MUL, TokenType::DIV}))
      {
         return new Binary(lhs, previous(), unary());
      }

      return lhs;
   }

   Expression * Parser::unary()
   {
      if(match({TokenType::SUB}))
      {
         return new Unary(previous(), unary());
      }

      return primary();
   }

   Expression * Parser::primary()
   {
      match({TokenType::INT});
      //TODO other Object types

      //if(t == TokenType::INT){
         return new Literal(new Int(previous().getIntVal()));
      //}
   }





   bool Parser::match(initializer_list<TokenType> types)
   {
      TokenType next = peek();
      for( TokenType t : types )
      {
         if(next == t){
            advance();
            return true;
         }
      }

      return false;
   }

   bool Parser::atEnd()
   {
      return pos >= tokens.size();
   }

   bool Parser::check(TokenType t)
   {
      if(atEnd()) return false;

      return t == peek();
   }

   TokenType Parser::peek()
   {
      return tokens[pos].type;
   }

   Token Parser::previous()
   {
      return tokens[pos -1];
   }

   Token Parser::advance()
   {
      if(!atEnd()) pos++;
      return previous();
   }


}

