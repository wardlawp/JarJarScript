#include <catch.hpp>
#include <Parser.h>
#include <vector>
#include <Token.h>
#include <TokenConstants.h>
#include <typeinfo>
#include <Tokenizer.h>
#include <Interpreter.h>

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
      Object * obj = i->visitExpression(literalExp);
      REQUIRE(typeid(*obj) == typeid(Int));
   }

   SECTION("Interpret Binary")
   {
      vector<Token> tokens = { Token(TokenType::INT, "32", 1), Token(TokenType::SUB, "-", 1), Token(TokenType::INT, "15", 1), Token(TokenType::EOL, ";", 1) };
      Parser p = Parser(tokens);
      Expression * binaryExpr = getExpression(p.eval().front());
      REQUIRE(typeid(*binaryExpr) == typeid(Binary));

      Object * obj = i->visitExpression(binaryExpr);
      REQUIRE(typeid(*obj) == typeid(Int));
      CHECK(obj->toStr() == "17");
   }

   SECTION("Concat String")
   {
      vector<Token> tokens = { Token(TokenType::STRING, "Hello ", 1), Token(TokenType::ADD, "+", 1), Token(TokenType::STRING, "World!", 1), Token(TokenType::EOL, ";", 1) };
      Parser p = Parser(tokens);
      Expression * binaryExpr = getExpression(p.eval().front());


      Object * obj = i->visitExpression(binaryExpr);
      REQUIRE(typeid(*obj) == typeid(String));
      String * sObj = dynamic_cast<String*>(obj);
      CHECK(sObj->val == "Hello World!");
   }

   SECTION("Interpret Nested 1")
   {
      string input = "7/3+5-8*4/1;"; //result: 2 + 5 - 8*4 = 7-32 = -25
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());


      Object * obj = i->visitExpression(ast);
      REQUIRE(typeid(*obj) == typeid(Int));
      CHECK(obj->toStr() == "-25");
   }

   SECTION("Interpret greater than")
   {
      vector<Token> tokens = Tokenizer("5>4;").getTokens();
      Expression * binaryComparison = getExpression(Parser(tokens).eval().front());


      Object * obj = i->visitExpression(binaryComparison);
      REQUIRE(typeid(*obj) == typeid(Bool));

      Bool * bObj = dynamic_cast<Bool*>(obj);
      CHECK(bObj->val == true);
   }

   SECTION("Interpret Nested 2")
   {
      string input = "(7/3+5-8*4/1)==-25;"; //result: 2 + 5 - 8*4 = 7-32 = -25
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());


      Object * obj = i->visitExpression(ast);
      Bool * bObj = dynamic_cast<Bool*>(obj);
      CHECK(bObj->val == true);
   }

   SECTION("Interpret Nested 3")
   {
      string input = "\"hel\"+\"lo\"==\"hello\";"; // "hel" + "lo" == "hello"
      vector<Token> tokens = Tokenizer(input).getTokens();
      Expression * ast = getExpression(Parser(tokens).eval().front());


      Object * obj = i->visitExpression(ast);
      Bool * bObj = dynamic_cast<Bool*>(obj);
      CHECK(bObj->val == true);
   }

   SECTION("Miss matching types Throws Exception")
   {
     string input = "5+\"5\";"; // int + string
     vector<Token> tokens = Tokenizer(input).getTokens();
     Expression * ast = getExpression(Parser(tokens).eval().front());

     REQUIRE_THROWS_AS(i->visitExpression(ast), TypeMissMatchException);
   }
}

TEST_CASE( "Interpret Statments", "Statments" )
{
   Interpreter *i = new Interpreter();

   SECTION("Print statement")
   {
     string input = "print \"test\";"; // int + string
     vector<Token> tokens = Tokenizer(input).getTokens();
     Statement * statement = Parser(tokens).eval().front();

     //Capture std out
     streambuf* oldCoutStreamBuf = cout.rdbuf();
     ostringstream strCout;
     cout.rdbuf( strCout.rdbuf() );

     //Run print statement
     i->visitStatement(statement);


     //restore old stream
     cout.rdbuf( oldCoutStreamBuf );

     CHECK(strCout.str() == "\"test\"");
   }
}
