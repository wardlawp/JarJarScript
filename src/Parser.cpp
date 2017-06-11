#include <Parser.h>

namespace JarJar
{

   Parser::Parser(vector<Token> tokens)
   {
      this->tokens = tokens;
      pos = 0;
   }

   vector<Statement*> Parser::eval()
   {
      vector<Statement*> result = vector<Statement*>();

      while (!atEnd()) {
         result.push_back(declaration());
      }

      return result;
   }

   Statement * Parser::declaration()
   {
      if(match({ TokenType::VAR }))
      {
         expect(TokenType::IDENTIFIER);
         Token name = previous();

         if(match({ TokenType::ASSIGN })){
            Expression * e = expression();
            expect(TokenType::EOL);
            return new VariableStatment(name,e);
         }

         expect(TokenType::EOL);
         return new VariableStatment(name,0);

      }

      return statement();
   }


   Statement * Parser::statement()
   {
      if(match({ TokenType::PRINT }))
      {
         return printStatement();
      } else if(match({ TokenType::LBRACKET }))
      {
         return block();
      }

      return expressionStatement();
   }

   Statement * Parser::printStatement()
   {
      Expression * e = expression();
      expect(TokenType::EOL);
      return new PrintStatment(e);
   }

   Statement * Parser::expressionStatement()
   {
      Expression * e = expression();
      expect(TokenType::EOL);
      return new ExpressionStatment(e);
   }

   Statement * Parser::block()
   {
      vector<Statement*> statements = vector<Statement*>();

      while(!check(TokenType::RBRACKET) and !atEnd())
      {
         statements.push_back(declaration());
      }

      expect(TokenType::RBRACKET);
      return new Block(statements);
   }

   Expression * Parser::expression()
   {
      return assign();
   }

   Expression * Parser::assign()
   {
      Expression * lvalue = equality();

      if(match( { TokenType::ASSIGN })){

         if(typeid(Variable) == typeid(*lvalue))
         {
            Variable * var = dynamic_cast<Variable*>(lvalue);
            return new Assign(var->name, assign());
         }

         throw new ParserException(previous(), "Invalid assignment target");
      }

      return lvalue;
   }

   Expression * Parser::equality()
   {
      Expression * expr = comparison();

      while (match( { TokenType::EQUALS, TokenType::NOT_EQUALS })) {
         expr = new Binary(expr, previous(), comparison());
      }

      return expr;
   }

   Expression * Parser::comparison()
   {
      Expression * expr = term();

      while (match( { TokenType::LT, TokenType::LTE, TokenType::GT,
            TokenType::GTE })) {
         expr = new Binary(expr, previous(), term());
      }

      return expr;
   }

   Expression * Parser::term()
   {
      Expression * expr = factor();

      while (match( { TokenType::ADD, TokenType::SUB })) {
         expr = new Binary(expr, previous(), factor());
      }

      return expr;
   }

   Expression * Parser::factor()
   {
      Expression * expr = unary();

      while (match( { TokenType::MUL, TokenType::DIV })) {
         expr = new Binary(expr, previous(), unary());
      }

      return expr;
   }

   Expression * Parser::unary()
   {
      if (match( { TokenType::SUB, TokenType::NOT })) {
         return new Unary(previous(), unary());
      }

      return primary();
   }

   Expression * Parser::primary()
   {
      TokenType next = peek();

      if (next == TokenType::INT) {
         Literal * result = new Literal(new Int(tokens.at(pos).getIntVal()));
         advance();
         return result;
      } else if (next == TokenType::STRING) {
         Literal * result = new Literal(
               new String(tokens.at(pos).getStringVal()));
         advance();
         return result;
      } else if (next == TokenType::BOOL) {
         Literal * result = new Literal(new Bool(tokens.at(pos).getBoolVal()));
         advance();
         return result;
      }else if (next == TokenType::DECIMAL) {
         Literal * result = new Literal(new Decimal(tokens.at(pos).getDoubleVal()));
         advance();
         return result;
      } else if (next == TokenType::LPAREN) {
         advance();
         Expression *e = equality();
         expect(TokenType::RPAREN);
         return new Grouping(e);
      } else if (next == TokenType::IDENTIFIER) {
         Variable *v = new Variable(tokens.at(pos));
         advance();
         return v;
      }

      string cusMsg = "Unexpected token '" + getStringRepr(next) + "'";
      throw ParserException(tokens.at(pos), cusMsg);

   }

   bool Parser::match(initializer_list<TokenType> types)
   {
      TokenType next = peek();
      for (TokenType t : types) {
         if (next == t) {
            advance();
            return true;
         }
      }

      return false;
   }

   bool Parser::atEnd()
   {
      return pos >= (tokens.size() - 1);
   }

   bool Parser::check(TokenType t)
   {
      if (atEnd())
         return false;

      return t == peek();
   }

   TokenType Parser::peek()
   {
      return tokens.at(pos).type;
   }

   Token Parser::previous()
   {
      return tokens.at(max(0, pos - 1));
   }

   Token Parser::advance()
   {
      if (!atEnd())
         pos++;
      return previous();
   }

   void Parser::expect(TokenType t)
   {
      if (!match( { t })) {
         string cusMsg = "Expected token '" + getStringRepr(t) + "'";
         throw ParserException(tokens.at(pos), cusMsg);
      }
   }
}

