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
      Expression * expr = comparison();

      while(match({TokenType::EQUALS, TokenType::NOT_EQUALS}))
      {
         expr = new Binary(expr, previous(), comparison());
      }

      return expr;
   }

   Expression * Parser::comparison()
   {
      Expression * expr = term();

      while(match({TokenType::LT, TokenType::LTE, TokenType::GT, TokenType::GTE}))
      {
         expr = new Binary(expr, previous(), term());
      }

      return expr;
   }

   Expression * Parser::term()
   {
      Expression * expr = factor();

      while(match({TokenType::ADD, TokenType::SUB}))
      {
         expr = new Binary(expr, previous(), factor());
      }

      return expr;
   }

   Expression * Parser::factor()
   {
      Expression * expr = unary();

      while(match({TokenType::MUL, TokenType::DIV}))
      {
         expr = new Binary(expr, previous(), unary());
      }

      return expr;
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
      TokenType next = peek();

      if(next == TokenType::INT){
         Literal * result = new Literal(new Int(tokens.at(pos).getIntVal()));
         advance();
         return result;
      } else if(next == TokenType::LPAREN){
         advance();
         Expression *e = equality();
         if(!match({TokenType::RPAREN})){
            string cusMsg =  "Expected token '" + getStringRepr(TokenType::RPAREN) + "'";
            throw ParserException(tokens.at(pos), cusMsg);
         }
         return new Grouping(e);
      }

      string cusMsg =  "Unexpected token '" + getStringRepr(next) + "'";
      throw ParserException(tokens.at(pos), cusMsg);

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
      return pos >= (tokens.size() -1);
   }

   bool Parser::check(TokenType t)
   {
      if(atEnd()) return false;

      return t == peek();
   }

   TokenType Parser::peek()
   {
      return tokens.at(pos).type;
   }

   Token Parser::previous()
   {
      return tokens.at(max(0,pos-1));
   }

   Token Parser::advance()
   {
      if(!atEnd()) pos++;
      return previous();
   }
}

