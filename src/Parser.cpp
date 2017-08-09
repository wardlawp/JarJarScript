#include <Parser.h>

namespace JarJar
{

   Parser::Parser(vector<Token> tokens)
   {
      this->tokens = tokens;
      pos = 0;
   }

   vector<shared_ptr<Statement>> Parser::eval()
   {
      auto result = vector<shared_ptr<Statement>>();

      while (!atEnd()) {
         auto ptr = shared_ptr<Statement>(declaration());
         result.push_back(ptr);
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
      } else if(match( { TokenType::IF })){
         return ifStatement();
      } else if(match( { TokenType::WHILE })){
         return whilE();
      } else if (match({ TokenType::FOR })) {
         return foR();
      }

      return expressionStatement();
   }

   /**
    * Perform syntactic desugaring
    * Expect: 'for' '(' varDeclaration | exprStatement | ':' expression? ';' expression? ')' statement
    * Produce: block { <varDeclaration> | <exprStatement>, while(<truth test>?){ <body>; <post statement>;? }
    *
    */
   Statement* Parser::foR()
   {
      expect(TokenType::LPAREN);

      Statement* initStatement = forInitStatement();
      Expression* truthTest = forExpression();
      Expression* postExpression = forExpression(false);
     
      if (truthTest == nullptr) {
         truthTest = new Literal(Bool::TRUE());
      }

      expect(TokenType::RPAREN);
      
      Statement* while_ = new WhileStatement(truthTest, forBody(postExpression));
      vector<Statement*> forDeSugared{ initStatement, while_ };

      return new Block(forDeSugared);
   }

   Block* Parser::forBody(Expression* postExpression)
   {
      Statement* body = statement();

      if (typeid(*body) != typeid(Block)) {
         body = new Block(vector<Statement*>{body});
      }

      if (postExpression != nullptr) {
         dynamic_cast<Block*>(body)->statements.push_back(new ExpressionStatment(postExpression));
      }

      return static_cast<Block*>(body);

   }

   Statement* Parser::forInitStatement()
   {
      if (match({ TokenType::EOL })) {
         return nullptr;
      }

      Statement* forInit = declaration();

      bool correctStatementType = (typeid(*forInit) == typeid(ExpressionStatment))
         || (typeid(*forInit) == typeid(VariableStatment));

      if (!correctStatementType) {
         string cusMsg = "Expected var declaration or expression statement.";
         throw ParserException(tokens.at(pos), cusMsg);
      }

      return forInit;
   }

   Statement* Parser::whilE()
   {
      expect(TokenType::LPAREN);
      Expression* truthTest = expression();
      expect(TokenType::RPAREN);

      return new WhileStatement(truthTest, statement());
   }

   Statement* Parser::ifStatement()
   {
      expect(TokenType::LPAREN);
      Expression* truthTest = expression();
      expect(TokenType::RPAREN);

      Statement* trueBranch = statement();
      Statement* falseBranch = nullptr;

      if(match({ TokenType::ELSE }))
      {
         falseBranch = statement();
      }

      return new IfStatement(truthTest, trueBranch, falseBranch);

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

      while(!check(TokenType::RBRACKET) && !atEnd())
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

   Expression * Parser::forExpression(bool consumeEOL)
   {
      Expression* expr = nullptr;
      if (!match({ TokenType::EOL }))
      {
         expr = expression();

         if (consumeEOL) {
            expect(TokenType::EOL);
         }
      }

      return expr;
   }

   Expression * Parser::assign()
   {
      Expression * lvalue = logicalOr();

      if(match( { TokenType::ASSIGN })){

         if(typeid(Variable) == typeid(*lvalue))
         {
            Variable * var = dynamic_cast<Variable*>(lvalue);
            Expression * result = new Assign(var->name, assign());
            delete var;
            return result;
         }

         throw ParserException(previous(), "Invalid assignment target");
      }

      return lvalue;
   }

   Expression * Parser::logicalOr()
   {
      Expression * lvalue = logicalAnd();
      if(match( { TokenType::OR })){
         Expression * right = logicalAnd();
         return new Logical(lvalue, TokenType::OR, right);
      }

      return lvalue;
   }

   Expression * Parser::logicalAnd()
   {
      Expression * lvalue = equality();
      if(match( { TokenType::AND })){
         Expression * right = equality();
         return new Logical(lvalue, TokenType::AND, right);
      }

      return lvalue;
   }


   Expression * Parser::equality()
   {
      Expression * expr = comparison();

      while (match( { TokenType::EQUALS, TokenType::NOT_EQUALS })) {
         Token op = previous();
         expr = new Binary(expr, op, comparison());
      }

      return expr;
   }

   Expression * Parser::comparison()
   {
      Expression * expr = term();

      while (match( { TokenType::LT, TokenType::LTE, TokenType::GT,
            TokenType::GTE })) {
         Token op = previous();
         expr = new Binary(expr, op, term());
      }

      return expr;
   }

   Expression * Parser::term()
   {
      Expression * expr = factor();

      while (match( { TokenType::ADD, TokenType::SUB })) {
         Token op = previous();
         expr = new Binary(expr, op , factor());
      }

      return expr;
   }

   Expression * Parser::factor()
   {
      Expression * expr = unary();

      while (match( { TokenType::MUL, TokenType::DIV })) {
         Token op = previous();
         expr = new Binary(expr, op, unary());
      }

      return expr;
   }

   Expression * Parser::unary()
   {
      if (match( { TokenType::SUB, TokenType::NOT })) {
         Token op = previous();
         return new Unary(op, unary());
      }

      return primary();
   }

   Expression * Parser::primary()
   {
      TokenType next = peek();

      if (next == TokenType::INT) {
         Object* into= new Int(tokens.at(pos).getIntVal());
         Literal * result = new Literal(into);
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

