#include <catch.hpp>
#include <ASTPrinter.h>
#include <Object.h>
#include <AST.h>
#include <Token.h>

using namespace JarJar;

TEST_CASE( "ASTPrinter can print different expressions", "Print AST expressions" )
{
   ASTPrinter print = ASTPrinter();

   SECTION("Print Literal")
   {
      string output = print.visitLiteral(new Literal(new Int(1)));
      REQUIRE(output == "1");
   }

   SECTION("Print Grouping")
   {
      string output = print.visitGrouping(new Grouping(new Literal(new Int(1))));
      REQUIRE(output == "(1)");
   }

   SECTION("Print Binary")
   {
      Binary *b = new Binary(new Literal(new Int(2)), Token(TokenType::ADD, "+", 1), new Literal(new Int(4)));
      string output = print.visitBinary(b);
      REQUIRE(output == "2 + 4");
   }

   SECTION("Print Binary")
   {
      Expression * u = new Unary(Token(TokenType::SUB, "-", 1), new Literal(new Int(4)));
      string output = print.visitExpression(u);
      REQUIRE(output == "- 4");
   }
}

TEST_CASE( "ASTPrinter can print nested expressions", "Print nested expressions" )
{
   //Expression: 44 * ((23 - 64) / (55 + 4))
   Binary *innerA = new Binary(new Literal(new Int(23)), Token(TokenType::SUB, "-", 1), new Literal(new Int(64)));
   Grouping *innerGroupA = new Grouping(innerA);

   Binary *innerB = new Binary(new Literal(new Int(55)), Token(TokenType::ADD, "+", 1), new Literal(new Int(4)));
   Grouping *innerGroupB = new Grouping(innerB);

   Binary *inner = new Binary(innerGroupA, Token(TokenType::DIV, "/", 1), innerGroupB);
   Grouping *group = new Grouping(inner);
   Expression * final = new Binary(new Literal(new Int(44)), Token(TokenType::MUL, "*", 1), group);

   ASTPrinter print = ASTPrinter();
   string output = print.visitExpression(final);
   REQUIRE(output == "44 * ((23 - 64) / (55 + 4))");
}



TEST_CASE( "Automatically shows nesting", "Printer nests" )
{
   //Expression: 32 + (55/23)
   Binary *inner = new Binary(new Literal(new Int(55)), Token(TokenType::DIV, "/", 1), new Literal(new Int(23)));
   Expression * e = new Binary(new Literal(new Int(32)), Token(TokenType::ADD, "+", 1), inner);

   ASTPrinter * print = new ASTPrinter();
   REQUIRE(print->visitExpression(e) == "32 + (55 / 23)");
}
