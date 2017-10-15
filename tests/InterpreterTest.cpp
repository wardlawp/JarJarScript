#include <catch.hpp>
#include <vector>
#include <Token.h>
#include <TokenConstants.h>
#include <typeinfo>
#include <Interpreter.h>
#include <Typedefs.h>
#include <memory>
#include <TestHelpers.h>
#include <queue>

using namespace std;
using namespace JarJar;

TEST_CASE( "Interpret Expressions", "Expressions" )
{
   auto interp = unique_ptr<Interpreter>(new Interpreter());
   Interpreter *i = interp.get();

   SECTION("Interpret Literal")
   {
      vector<Token> tokens = { Token(TokenType::INT, "5", 1), Token(TokenType::EOL, ";", 1)  };

      auto statements = parse(tokens);
      Expression * literalExp = getFirstExpression(statements);

      REQUIRE(typeid(*literalExp) == typeid(Literal));


      SObject obj = i->visitExpression(literalExp);
      REQUIRE(typeid(*obj.get()) == typeid(Int));
   }

   SECTION("Interpret Binary")
   {
      vector<Token> tokens = 
      { 
         Token(TokenType::INT, "32", 1),
         Token(TokenType::SUB, "-", 1),
         Token(TokenType::INT, "15", 1),
         Token(TokenType::EOL, ";", 1) 
      };

      auto statements = parse(tokens);
      Expression * binaryExpr = getFirstExpression(statements);


      REQUIRE(typeid(*binaryExpr) == typeid(Binary));

      SObject obj = i->visitExpression(binaryExpr);
      REQUIRE(typeid(*obj.get()) == typeid(Int));
      CHECK(obj->toStr() == "17");
   }

   SECTION("Concat String")
   {
      vector<Token> tokens = 
      { 
         Token(TokenType::STRING, "Hello ", 1), 
         Token(TokenType::ADD, "+", 1), 
         Token(TokenType::STRING, "World!", 1), 
         Token(TokenType::EOL, ";", 1) 
};

      auto statements = parse(tokens);
      Expression * binaryExpr = getFirstExpression(statements);

      SObject obj = i->visitExpression(binaryExpr);
      REQUIRE(typeid(*obj.get()) == typeid(String));
      String * sObj = dynamic_cast<String*>(obj.get());
      CHECK(sObj->val == "Hello World!");
   }

   SECTION("Interpret Nested 1")
   {
      //result: 2 + 5 - 8*4 = 7-32 = -25
      vector<Token> tokens = stringToTokens("7/3+5-8*4/1;");

      auto statements = parse(tokens);
      Expression * ast = getFirstExpression(statements);

      SObject obj = i->visitExpression(ast);
      REQUIRE(typeid(*obj.get()) == typeid(Int));
      CHECK(obj->toStr() == "-25");
   }

   SECTION("Interpret greater than")
   {
      vector<Token> tokens = stringToTokens("5>4;");

      auto statements = parse(tokens);
      Expression * binaryComparison = getFirstExpression(statements);

      SObject obj = i->visitExpression(binaryComparison);
      REQUIRE(typeid(*obj.get()) == typeid(Bool));

      Bool * bObj = dynamic_cast<Bool*>(obj.get());
      CHECK(bObj->val == true);
   }

   SECTION("Interpret Nested 2")
   {
      //result: 2 + 5 - 8*4 = 7-32 = -25
      vector<Token> tokens = stringToTokens("(7/3+5-8*4/1)==-25;");

      auto statements = parse(tokens);
      Expression * ast = getFirstExpression(statements);

      SObject obj = i->visitExpression(ast);
      Bool * bObj = dynamic_cast<Bool*>(obj.get());
      CHECK(bObj->val == true);
   }

   SECTION("Interpret Nested 3")
   {
      // "hel" + "lo" == "hello"
      vector<Token> tokens = stringToTokens("\"hel\"+\"lo\"==\"hello\";");

      auto statements = parse(tokens);
      Expression * ast = getFirstExpression(statements);

      SObject obj = i->visitExpression(ast);
      Bool * bObj = dynamic_cast<Bool*>(obj.get());
      CHECK(bObj->val == true);
   }

   SECTION("Miss matching types Throws Exception")
   {
      // int + string
      vector<Token> tokens = stringToTokens("5+\"5\";");

      auto statements = parse(tokens);
      Expression * ast = getFirstExpression(statements);

      REQUIRE_THROWS_AS(i->visitExpression(ast), TypeMissMatchException);
   }

   SECTION("Variable Expression")
   {
      //Setup: Interpreter with environment and variable
      vector<Token> tokens = stringToTokens("var a = 5;");
      auto statements = parse(tokens);
      Statement * statement = statements.front().get();

      i->visitStatement(statement);

      //Act: Interpreter interprets a VaraiableExpression
      tokens = stringToTokens("a;");
      statements = parse(tokens);
      Expression * ast = getFirstExpression(statements);
      REQUIRE(typeid(*ast) == typeid(Variable));

      SObject result = i->visitExpression(ast);

      //Assert: Interpreter returns variable
      REQUIRE(typeid(*result.get()) == typeid(Int));
      Int* resultInt = dynamic_cast<Int*>(result.get());

      CHECK(resultInt->val == 5);
   }

   SECTION("Logical Expression")
   {
      vector<Token> tokens = stringToTokens("5 and 6;");

      auto statements = parse(tokens);
      Expression * logical = getFirstExpression(statements);
      SObject obj = i->visitExpression(logical);

      REQUIRE(typeid(*obj.get()) == typeid(Int));
      Int * intObj = dynamic_cast<Int*>(obj.get());
      CHECK(intObj->val == 6);

      tokens = stringToTokens("\"\" or \"wabbits\";");

      auto statements2 = parse(tokens);
      logical = getFirstExpression(statements2);
      obj = i->visitExpression(logical);

      REQUIRE(typeid(*obj.get()) == typeid(String));
      String * sObj = dynamic_cast<String*>(obj.get());
      CHECK(sObj->val == "wabbits");
   }

   SECTION("Assignment expression")
   {
      //Setup: Declare Variable
      vector<Token> tokens = stringToTokens("var a;");
      auto statements = parse(tokens);
      Statement * statement = statements.front().get();

      i->visitStatement(statement);


      //Act: Interpreter interprets assignement expression
      tokens = stringToTokens("a = 5;");
      statements = parse(tokens);
      Expression * ast = getFirstExpression(statements);
      REQUIRE(typeid(*ast) == typeid(Assign));

      //Assert declared but not initialized
      REQUIRE(i->getVar("a").get() == Null::addr());

      //Act: visit the assignment
      i->visitExpression(ast);

      //Assert assigned
      SObject result = i->getVar("a");
      REQUIRE(typeid(*result.get()) == typeid(Int));
      Int* resultInt = dynamic_cast<Int*>(result.get());

      CHECK(resultInt->val == 5);
   }

   SECTION("Call expression")
   {
      auto output = queue<string>();
      i = new Interpreter(&output);

      //Declare function
      vector<Token> tokens = stringToTokens("fun a(b){ print b; }");
      auto statements = parse(tokens);
      i->visitStatement(statements[0].get());
      
      //Call function
      tokens = stringToTokens("a(\"test\");");
      statements = parse(tokens);
      i->visitStatement(statements[0].get());

      REQUIRE(output.size() == 1);
      CHECK(output.front() == "\"test\"");
      delete i;
   }
}

TEST_CASE( "Interpret Statements", "Statements" )
{
   auto interp = unique_ptr<Interpreter>(new Interpreter());
   Interpreter *i = interp.get();

   SECTION("Print statement")
   {
      auto output = queue<string>();
      i = new Interpreter(&output);

      vector<Token> tokens = stringToTokens("print \"test\";");

      auto statements = parse(tokens);
      Statement * statement = statements.front().get();

      //Run print statement
      i->visitStatement(statement);

      REQUIRE(output.size() == 1);
      CHECK(output.front() == "\"test\"");
      delete i;
   }

   SECTION("Variable statement")
   {
      vector<Token> tokens = stringToTokens("var a = 5;");
      auto statements = parse(tokens);
      Statement * statement = statements.front().get();

      i->visitStatement(statement);

      SObject result = i->getVar("a");
      REQUIRE(typeid(*result.get()) == typeid(Int));

      Int * obj = dynamic_cast<Int*>(result.get());

      CHECK(obj->val == 5);
   }

   SECTION("If statement")
   {
      auto output = queue<string>();
      i = new Interpreter(&output);

      vector<Token> tokens = stringToTokens("ifsa(ya == ya) {print \"test\";} elsa { print \"boo\";}");

      auto statements = parse(tokens);
      Statement * statement = statements.front().get();

      //Run print statement
      i->visitStatement(statement);

      tokens = stringToTokens("ifsa(na == ya) {print \"nooo\";} elsa { print \"yusssss\";}");

      statements = parse(tokens);
      statement = statements.front().get();
      i->visitStatement(statement);

      REQUIRE(output.size() == 2);
      CHECK(output.front() == "\"test\"");
      output.pop();
      CHECK(output.front() == "\"yusssss\"");

      delete i;
   }

   SECTION("While statement")
   {
      auto output = queue<string>();
      i = new Interpreter(&output);

      vector<Token> tokens = stringToTokens("var a = 3; while(a){ print a; a = a-1; }");

      auto statements = parse(tokens);
      REQUIRE(statements.size() == 2);

      //Run the two statements
      i->visitStatement(statements[0].get());
      i->visitStatement(statements[1].get());

      REQUIRE(output.size() == 3);
      CHECK(output.front() == "3");
      output.pop();
      CHECK(output.front() == "2");
      output.pop();
      CHECK(output.front() == "1");


      delete i;
   }

  

   SECTION("Block Statment")
   {
      vector<Token> tokens = stringToTokens("var a; { a = 5;  a = a - 2; }");
      auto statements = parse(tokens);

      REQUIRE(statements.size() == 2);

      i->visitStatement(statements[0].get());
      i->visitStatement(statements[1].get());

      SObject result = i->getVar("a");
      REQUIRE(typeid(*result.get()) == typeid(Int));
            
      Int * obj = dynamic_cast<Int*>(result.get());

      CHECK(obj->val == 3);
   }

   SECTION("Function Declaration Statment")
   {
      vector<Token> tokens = stringToTokens("fun a(b){ print b; }");
      auto statements = parse(tokens);

      REQUIRE(statements.size() == 1);

      i->visitStatement(statements[0].get());

      SObject result = i->getVar("a");
      REQUIRE(typeid(*result.get()) == typeid(Function));

      Function * obj = dynamic_cast<Function*>(result.get());

      CHECK(obj->arity() == 1);
   }
}
