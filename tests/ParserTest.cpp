#include <catch.hpp>
#include <Parser.h>
#include <Statement.h>
#include <vector>
#include <Token.h>
#include <TokenConstants.h>
#include <typeinfo>
#include <Tokenizer.h>
#include <memory>
#include <TestHelpers.h>

using namespace std;
using namespace JarJar;


TEST_CASE( "Parser matches basic grammars", "Parser match grammar" )
{


   SECTION("Match Primary")
   {
      vector<Token> tokens = { Token(TokenType::INT, "5", 1), Token(TokenType::EOL, ";", 1) };
      Parser p = Parser(tokens);

      auto statements = p.eval();
      Expression * result = getFirstExpression(statements);
      REQUIRE(typeid(*result) == typeid(Literal));

      Literal * lit = dynamic_cast<Literal*>(result);
      REQUIRE(typeid(*lit->value.get()) == typeid(Int));
      REQUIRE(lit->value.get()->toStr() == "5");
   }

   //TODO match more types of primaries (string, bool, null, grouping)

   SECTION("Match Unary")
   {
      vector<Token> tokens = { Token(TokenType::SUB, "-", 1), Token(TokenType::INT, "32", 1), Token(TokenType::EOL, ";", 1) };
      Parser p = Parser(tokens);

      auto statements = p.eval();
      Expression * result = getFirstExpression(statements);
      REQUIRE(typeid(*result) == typeid(Unary));

      Unary * un = dynamic_cast<Unary*>(result);
      REQUIRE(un->op.type == TokenType::SUB);
      REQUIRE(typeid(*un->right) == typeid(Literal));

      Literal * lit = dynamic_cast<Literal*>(un->right);
      REQUIRE(typeid(*lit->value.get()) == typeid(Int));
      REQUIRE(lit->value.get()->toStr() == "32");
   }

   SECTION("Match Nested")
   {
      /**
       * The phrase "7/3+5-8*4/1" should be parsed in to the following
       * AST:
       *           -
       *       +       /
       *    /    5   *    1
       *  7   3    8   4
       *
       *
       * AKA:
       *         root
       *     left1    right1
       *  left2    right2
       */

      string input = "7/3+5-8*4/1;";
      vector<Token> tokens = Tokenizer(input).getTokens();
      auto statements = Parser(tokens).eval();
      Expression * result = getFirstExpression(statements);


      REQUIRE(typeid(*result) == typeid(Binary));
      Binary * root = dynamic_cast<Binary*>(result);
      CHECK(root->op.type == TokenType::SUB);
      REQUIRE(typeid(*root->left) == typeid(Binary));
      REQUIRE(typeid(*root->right) == typeid(Binary));

      Binary * left1 = dynamic_cast<Binary*>(root->left);
      CHECK(left1->op.type == TokenType::ADD);
      REQUIRE(typeid(*left1->left) == typeid(Binary));
      REQUIRE(typeid(*left1->right) == typeid(Literal));

      Literal * left1Right = dynamic_cast<Literal*>(left1->right);
      REQUIRE(typeid(*left1Right->value.get()) == typeid(Int));

      Int * five = dynamic_cast<Int*>(left1Right->value.get());
      CHECK(five->val == 5);

      Binary * left2 = dynamic_cast<Binary*>(left1->left);
      CHECK(left2->op.type == TokenType::DIV);
      CHECK(typeid(*left2->left) == typeid(Literal));
      CHECK(typeid(*left2->right) == typeid(Literal));

      Binary * right1 = dynamic_cast<Binary*>(root->right);
      CHECK(right1->op.type == TokenType::DIV);
      REQUIRE(typeid(*right1->left) == typeid(Binary));
      REQUIRE(typeid(*right1->right) == typeid(Literal));

      Literal * right1Right = dynamic_cast<Literal*>(right1->right);
      REQUIRE(typeid(*right1Right->value.get()) == typeid(Int));

      Int * one = dynamic_cast<Int*>(right1Right->value.get());
      CHECK(one->val == 1);


      Binary * right2 = dynamic_cast<Binary*>(right1->left);
      CHECK(right2->op.type == TokenType::MUL);
      CHECK(typeid(*right2->left) == typeid(Literal));
      CHECK(typeid(*right2->right) == typeid(Literal));
   }

   SECTION("Match Grouping")
   {
      string input = "(5+6);";
      vector<Token> tokens = Tokenizer(input).getTokens();
      auto statements = Parser(tokens).eval();
      Expression * result = getFirstExpression(statements);

      REQUIRE(typeid(*result) == typeid(Grouping));
      Grouping * root = dynamic_cast<Grouping*>(result);
      REQUIRE(typeid(*root->exp) == typeid(Binary));

      Binary * subExp = dynamic_cast<Binary*>(root->exp);
      CHECK(typeid(*subExp->left) == typeid(Literal));
      CHECK(subExp->op.type == TokenType::ADD);
      CHECK(typeid(*subExp->right) == typeid(Literal));
   }

   SECTION("Incomplete Grouping Throws Exception")
   {
     string input = "(5+6";
     vector<Token> tokens = Tokenizer(input).getTokens();
     REQUIRE_THROWS_AS(Parser(tokens).eval(), ParserException);
   }

   SECTION("Match ExpressionStatement")
   {
      vector<Token> tokens = { Token(TokenType::INT, "5", 1), Token(TokenType::EOL, ";", 1) };

      auto statements = Parser(tokens).eval();
      Statement * result = statements.front().get();

      REQUIRE(typeid(*result) == typeid(ExpressionStatment));
      ExpressionStatment * stmt = dynamic_cast<ExpressionStatment*>(result);

      REQUIRE(typeid(*stmt->expr) == typeid(Literal));

      Literal * literal =  dynamic_cast<Literal*>(stmt->expr);
      REQUIRE(typeid(*literal->value.get()) == typeid(Int));

      Int * val = dynamic_cast<Int*>(literal->value.get());
      CHECK(val->val == 5);
   }

   SECTION("Match VariableStatement with initializer")
   {
      string input = "var abc = 5;";
      vector<Token> tokens = Tokenizer(input).getTokens();

      auto statements = Parser(tokens).eval();
      Statement * result = statements.front().get();

      REQUIRE(typeid(*result) == typeid(VariableStatment));
      VariableStatment * stmt = dynamic_cast<VariableStatment*>(result);

      CHECK(stmt->name.type == TokenType::IDENTIFIER);

      REQUIRE(typeid(*stmt->expr) == typeid(Literal));

      Literal * literal =  dynamic_cast<Literal*>(stmt->expr);
      REQUIRE(typeid(*literal->value.get()) == typeid(Int));

      Int * val = dynamic_cast<Int*>(literal->value.get());
      CHECK(val->val == 5);
   }

   SECTION("Match VariableStatement without initializer")
   {
      string input = "var abc;";
      vector<Token> tokens = Tokenizer(input).getTokens();

      auto statements = Parser(tokens).eval();
      Statement * result = statements.front().get();

      REQUIRE(typeid(*result) == typeid(VariableStatment));
      VariableStatment * stmt = dynamic_cast<VariableStatment*>(result);

      CHECK(stmt->name.type == TokenType::IDENTIFIER);

      CHECK(stmt->expr == 0);
   }

   SECTION("Match Variable")
   {
      string input = "abc;";
      vector<Token> tokens = Tokenizer(input).getTokens();

      auto statements = Parser(tokens).eval();
      Expression * result = getFirstExpression(statements);

      REQUIRE(typeid(*result) == typeid(Variable));
      Variable * var = dynamic_cast<Variable*>(result);

      CHECK(var->name.value == "abc");
   }

   SECTION("Match Assign")
   {
      string input = "abc = 32;";
      vector<Token> tokens = Tokenizer(input).getTokens();

      auto statements = Parser(tokens).eval();
      Expression * result = getFirstExpression(statements);

      REQUIRE(typeid(*result) == typeid(Assign));
      Assign * assign = dynamic_cast<Assign*>(result);

      CHECK(assign->name.value == "abc");

      REQUIRE(typeid(*assign->exp) == typeid(Literal));
      Literal * lit = dynamic_cast<Literal*>(assign->exp);

      REQUIRE(typeid(*lit->value.get()) == typeid(Int));
      Int * obj = dynamic_cast<Int*>(lit->value.get());

      CHECK(obj->val == 32);
   }

   SECTION("Match Block")
   {
      string input = "{ print \"hi\"; }";
      vector<Token> tokens = Tokenizer(input).getTokens();

      auto statements = Parser(tokens).eval();
      Statement * result = statements.front().get();

      REQUIRE(typeid(*result) == typeid(Block));
      Block * block = dynamic_cast<Block*>(result);

      REQUIRE(block->statements.size() == 1);

      REQUIRE(typeid(*block->statements[0]) == typeid(PrintStatment));
      PrintStatment * print = dynamic_cast<PrintStatment*>(block->statements[0]);

      REQUIRE(typeid(*print->expr) == typeid(Literal));
      Literal * lit = dynamic_cast<Literal*>(print->expr);

      REQUIRE(typeid(*lit->value.get()) == typeid(String));
      String * obj = dynamic_cast<String*>(lit->value.get());

      CHECK(obj->val == "hi");
   }

   SECTION("Match Block with multiple Statments")
   {
      string input = "{ print \"hi\"; print \"hi\"; }";
      vector<Token> tokens = Tokenizer(input).getTokens();


      auto statements = Parser(tokens).eval();
      Statement * result = statements.front().get();

      REQUIRE(typeid(*result) == typeid(Block));
      Block * block = dynamic_cast<Block*>(result);

      CHECK(block->statements.size() == 2);
   }
}
