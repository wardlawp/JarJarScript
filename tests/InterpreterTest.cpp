#include <catch.hpp>
#include <Parser.h>
#include <vector>
#include <Token.h>
#include <TokenConstants.h>
#include <typeinfo>
#include <Tokenizer.h>
#include <Interpreter.h>
#include <Typedefs.h>

using namespace std;
using namespace JarJar;

/* Testing helper function, defined in ParserTest.cpp */
Expression * getExpression(Statement * statement);


TEST_CASE( "Interpret Expressions", "Expressions" )
{
   Interpreter *i = new Interpreter();

   SECTION("Interpret Literal")
   {
      vector<Token> tokens = { Token(TokenType::INT, "5", 1), Token(TokenType::EOL, ";", 1)  };
      Parser p = Parser(tokens);
      Expression * literalExp = getExpression(p.eval().front());
      REQUIRE(typeid(*literalExp) == typeid(Literal));

      //TODO make visitExpression private?
      SafeObject obj = i->visitExpression(literalExp);
      REQUIRE(typeid(*obj.get()) == typeid(Int));
   }

   SECTION("Interpret Binary")
   {
      vector<Token> tokens = { Token(TokenType::INT, "32", 1), Token(TokenType::SUB, "-", 1), Token(TokenType::INT, "15", 1), Token(TokenType::EOL, ";", 1) };
      Parser p = Parser(tokens);
      Expression * binaryExpr = getExpression(p.eval().front());
      REQUIRE(typeid(*binaryExpr) == typeid(Binary));

      SafeObject obj = i->visitExpression(binaryExpr);
      REQUIRE(typeid(*obj.get()) == typeid(Int));
      CHECK(obj->toStr() == "17");
   }

   SECTION("Concat String")
   {
      vector<Token> tokens = { Token(TokenType::STRING, "Hello ", 1), Token(TokenType::ADD, "+", 1), Token(TokenType::STRING, "World!", 1), Token(TokenType::EOL, ";", 1) };
      Parser p = Parser(tokens);
      Expression * binaryExpr = getExpression(p.eval().front());


      SafeObject obj = i->visitExpression(binaryExpr);
      REQUIRE(typeid(*obj.get()) == typeid(String));
      String * sObj = dynamic_cast<String*>(obj.get());
      CHECK(sObj->val == "Hello World!");
   }

   SECTION("Interpret Nested 1")
   {
      string input = "7/3+5-8*4/1;"; //result: 2 + 5 - 8*4 = 7-32 = -25
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());


      SafeObject obj = i->visitExpression(ast);
      REQUIRE(typeid(*obj.get()) == typeid(Int));
      CHECK(obj->toStr() == "-25");
   }

   SECTION("Interpret greater than")
   {
      vector<Token> tokens = Tokenizer("5>4;").getTokens();
      Expression * binaryComparison = getExpression(Parser(tokens).eval().front());


      SafeObject obj = i->visitExpression(binaryComparison);
      REQUIRE(typeid(*obj.get()) == typeid(Bool));

      Bool * bObj = dynamic_cast<Bool*>(obj.get());
      CHECK(bObj->val == true);
   }

   SECTION("Interpret Nested 2")
   {
      string input = "(7/3+5-8*4/1)==-25;"; //result: 2 + 5 - 8*4 = 7-32 = -25
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());


      SafeObject obj = i->visitExpression(ast);
      Bool * bObj = dynamic_cast<Bool*>(obj.get());
      CHECK(bObj->val == true);
   }

   SECTION("Interpret Nested 3")
   {
      string input = "\"hel\"+\"lo\"==\"hello\";"; // "hel" + "lo" == "hello"
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());


      SafeObject obj = i->visitExpression(ast);
      Bool * bObj = dynamic_cast<Bool*>(obj.get());
      CHECK(bObj->val == true);
   }

   SECTION("Miss matching types Throws Exception")
   {
      string input = "5+\"5\";"; // int + string
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());

      REQUIRE_THROWS_AS(i->visitExpression(ast), TypeMissMatchException);
   }

   SECTION("Variable Expression")
   {
     //TODO
   }
}

TEST_CASE( "Interpret Statments", "Statments" )
{
   Interpreter *i = new Interpreter();

   SECTION("Print statement")
   {
      vector<string> output = vector<string>();
      i = new Interpreter(&output);

      string input = "print \"test\";";
      vector<Token> tokens = Tokenizer(input).getTokens();
      Statement * statement = Parser(tokens).eval().front();


      //Run print statement
      i->visitStatement(statement);


      REQUIRE(output.size() == 1);
      CHECK(output[0] == "\"test\"");
   }

   SECTION("Variable statement")
   {
      string input = "var a = 5;";
      vector<Token> tokens = Tokenizer(input).getTokens();
      Statement * statement = Parser(tokens).eval().front();
      i->visitStatement(statement);

      SafeObject result = i->getVar("a");
      REQUIRE(typeid(*result.get()) == typeid(Int));

      Int * obj = dynamic_cast<Int*>(result.get());

      CHECK(obj->val == 5);
   }

   //TODO test Assignment, block execution
}
