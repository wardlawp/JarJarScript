#include <catch.hpp>
#include <Parser.h>
#include <vector>
#include <Token.h>
#include <TokenConstants.h>
#include <typeinfo>

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


}
