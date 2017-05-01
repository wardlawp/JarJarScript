#include <catch.hpp>
#include <Parser.h>
#include <vector>
#include <Token.h>
#include <TokenConstants.h>
#include <typeinfo>
#include <Tokenizer.h>

using namespace std;
using namespace JarJar;

TEST_CASE( "Parser matches basic grammars", "Parser match grammar" )
{
   SECTION("Match Primary")
   {
      vector<Token> tokens = { Token(TokenType::INT, "5", 1) };
      Parser p = Parser(tokens);

      Expression * result = p.eval();
      REQUIRE(typeid(*result) == typeid(Literal));

      Literal * lit = dynamic_cast<Literal*>(result);
      REQUIRE(typeid(*lit->value) == typeid(Int));
      REQUIRE(lit->value->toStr() == "5");
   }

   //TODO match more types of primaries (string, bool, null, grouping)

   SECTION("Match Unary")
   {
      vector<Token> tokens = { Token(TokenType::SUB, "-", 1), Token(TokenType::INT, "32", 1) };
      Parser p = Parser(tokens);

      Expression * result = p.eval();
      REQUIRE(typeid(*result) == typeid(Unary));

      Unary * un = dynamic_cast<Unary*>(result);
      REQUIRE(un->op.type == TokenType::SUB);
      REQUIRE(typeid(*un->right) == typeid(Literal));

      Literal * lit = dynamic_cast<Literal*>(un->right);
      REQUIRE(typeid(*lit->value) == typeid(Int));
      REQUIRE(lit->value->toStr() == "32");
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

      string input = "7/3+5-8*4/1";
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * result = Parser(tokens).eval();


      REQUIRE(typeid(*result) == typeid(Binary));
      Binary * root = dynamic_cast<Binary*>(result);
      CHECK(root->op.type == TokenType::SUB);
      REQUIRE(typeid(*root->left) == typeid(Binary));
      REQUIRE(typeid(*root->right) == typeid(Binary));

      Binary * left1 = dynamic_cast<Binary*>(root->left);
      CHECK(left1->op.type == TokenType::ADD);
      REQUIRE(typeid(*left1->left) == typeid(Binary));
      REQUIRE(typeid(*left1->right) == typeid(Literal));

      Binary * left2 = dynamic_cast<Binary*>(left1->left);
      CHECK(left2->op.type == TokenType::DIV);
      CHECK(typeid(*left2->left) == typeid(Literal));
      CHECK(typeid(*left2->right) == typeid(Literal));

      Binary * right1 = dynamic_cast<Binary*>(root->right);
      CHECK(right1->op.type == TokenType::DIV);
      REQUIRE(typeid(*right1->left) == typeid(Binary));
      REQUIRE(typeid(*right1->right) == typeid(Literal));

      Binary * right2 = dynamic_cast<Binary*>(right1->left);
      CHECK(right2->op.type == TokenType::MUL);
      CHECK(typeid(*right2->left) == typeid(Literal));
      CHECK(typeid(*right2->right) == typeid(Literal));
   }

   SECTION("Match Grouping")
   {
      string input = "(5+6)";
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * result = Parser(tokens).eval();

      REQUIRE(typeid(*result) == typeid(Grouping));
      Grouping * root = dynamic_cast<Grouping*>(result);
      REQUIRE(typeid(*root->exp) == typeid(Binary));

      Binary * subExp = dynamic_cast<Binary*>(result);
      CHECK(typeid(*subExp->left) == typeid(Literal));
      CHECK(subExp->op.type == TokenType::ADD);
      CHECK(typeid(*subExp->right) == typeid(Literal));
   }

   //TODO Parser unexpected Token error handling
}
