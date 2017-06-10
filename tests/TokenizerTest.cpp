#include <catch.hpp>
#include <Tokenizer.h>
#include <Exceptions.h>
#include <iostream>

using namespace JarJar;
using namespace std;

// TODO
//- Tokenizer handles multiple lines
//- Tokenizer reads end line characters

#define TOKEN_CHECK(str, T) {\
        SECTION("Scan " str " operator"){ \
            Tokenizer t = Tokenizer(str); \
            vector<Token> result = t.getTokens(); \
            REQUIRE(result.size() == 1); \
            REQUIRE(result[0].type == T); \
        } \
    }

//- Tokenizer can scan operators +,-, /,*, =, !, ==, !=, >, <, >=, <=, (, )
TEST_CASE( "Tokenizer scans operators", "scan operators" )
{
   TOKEN_CHECK("+", TokenType::ADD);
   TOKEN_CHECK("-", TokenType::SUB);
   TOKEN_CHECK("*", TokenType::MUL);
   TOKEN_CHECK("/", TokenType::DIV);
   TOKEN_CHECK("=", TokenType::ASSIGN);
   TOKEN_CHECK("!", TokenType::NOT);
   TOKEN_CHECK("<", TokenType::LT);
   TOKEN_CHECK(">", TokenType::GT);
   TOKEN_CHECK("==", TokenType::EQUALS);
   TOKEN_CHECK("!=", TokenType::NOT_EQUALS);
   TOKEN_CHECK(">=", TokenType::GTE);
   TOKEN_CHECK("<=", TokenType::LTE);
   TOKEN_CHECK("(", TokenType::LPAREN);
   TOKEN_CHECK(")", TokenType::RPAREN);
}

//- Tokenizer can scan keywords AND, OR, IF, ELSE, BREAK, WHILE, FOR
TEST_CASE( "Tokenizer scans keywords", "scan operators" )
{
   TOKEN_CHECK("and", TokenType::AND);
   TOKEN_CHECK("or", TokenType::OR);
   TOKEN_CHECK("ifsa", TokenType::IF);
   TOKEN_CHECK("elsa", TokenType::ELSE);
   TOKEN_CHECK("break", TokenType::BREAK);
   TOKEN_CHECK("while", TokenType::WHILE);
   TOKEN_CHECK("for", TokenType::FOR);
   TOKEN_CHECK("var", TokenType::VAR);
}

//- Tokenizer can scan keywords AND, OR, IF, ELSE, BREAK, WHILE, FOR
TEST_CASE( "Tokenizer scans identifier", "scan identifier" )
{
   TOKEN_CHECK("my_var", TokenType::IDENTIFIER);
   TOKEN_CHECK("ClassName", TokenType::IDENTIFIER);
}

//- Tokenizer can scan primitives string, int, double, bool, null
TEST_CASE( "Tokenizer scans primitives", "scan operators" )
{
   SECTION("Scan int"){
      Tokenizer t = Tokenizer("123");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 1);
      REQUIRE(result[0].type == TokenType::INT);
      REQUIRE(result[0].getIntVal() == 123);
   }

   SECTION("Scan decimal") {
      Tokenizer t = Tokenizer("123.23");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 1);
      REQUIRE(result[0].type == TokenType::DECIMAL);
      REQUIRE(result[0].getDoubleVal() == 123.23);
   }

   SECTION("Scan string") {
      Tokenizer t = Tokenizer("\" hello \"");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 1);
      REQUIRE(result[0].type == TokenType::STRING);
      REQUIRE(result[0].getStringVal() == " hello ");
   }

   SECTION("Scan bool") {
      Tokenizer t = Tokenizer("na");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 1);
      REQUIRE(result[0].type == TokenType::BOOL);
      REQUIRE(result[0].getBoolVal() == false);

      t = Tokenizer("ya");
      result = t.getTokens();

      REQUIRE(result[0].getBoolVal() == true);
   }

   TOKEN_CHECK("nada", TokenType::NADA);
}

//- Tokenizer reads sequences of tokens
TEST_CASE( "Tokenizer scans sequnce of tokens", "scan sequence" )
{
   SECTION("Sequence 1"){
      Tokenizer t = Tokenizer(" na ya   123 \"hello !\" =+ != nada");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 8);

      CHECK(result[0].type == TokenType::BOOL);
      CHECK(result[0].getBoolVal() == false);

      CHECK(result[1].type == TokenType::BOOL);
      CHECK(result[1].getBoolVal() == true);

      CHECK(result[2].type == TokenType::INT);
      CHECK(result[2].getIntVal() == 123);

      CHECK(result[3].type == TokenType::STRING);
      CHECK(result[3].getStringVal() == "hello !");

      CHECK(result[4].type == TokenType::ASSIGN);

      CHECK(result[5].type == TokenType::ADD);

      CHECK(result[6].type == TokenType::NOT_EQUALS);

      CHECK(result[7].type == TokenType::NADA);
   }

   SECTION("Sequence 1") {
      Tokenizer t = Tokenizer("+===!4.123");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 5);

      CHECK(result[0].type == TokenType::ADD);

      CHECK(result[1].type == TokenType::EQUALS);

      CHECK(result[2].type == TokenType::ASSIGN);

      CHECK(result[3].type == TokenType::NOT);

      CHECK(result[4].type == TokenType::DECIMAL);
      CHECK(result[4].getDoubleVal() == 4.123);
   }
}

//- Tokenizer reads sequences of tokens
TEST_CASE( "Tokenizer handles whitespace", "whitespace" )
{
   SECTION("Sequence 1"){
      Tokenizer t = Tokenizer(" na ya   +/  +");
      vector<Token> result = t.getTokens();

      REQUIRE(result.size() == 5);

      CHECK(result[0].type == TokenType::BOOL);
      CHECK(result[0].value == "na");
      CHECK(result[1].type == TokenType::BOOL);
      CHECK(result[1].value == "ya");
      CHECK(result[2].type == TokenType::ADD);
      CHECK(result[2].value == "+");
      CHECK(result[3].type == TokenType::DIV);
      CHECK(result[3].value == "/");
      CHECK(result[4].type == TokenType::ADD);
      CHECK(result[4].value == "+");
   }

   SECTION("Sequence 2"){
     Tokenizer t = Tokenizer("5   + 6   / ");
     vector<Token> result = t.getTokens();

     REQUIRE(result.size() == 4);

     CHECK(result[0].type == TokenType::INT);
     CHECK(result[0].value == "5");
     CHECK(result[1].type == TokenType::ADD);
     CHECK(result[1].value == "+");
     CHECK(result[2].type == TokenType::INT);
     CHECK(result[2].value == "6");
     CHECK(result[3].type == TokenType::DIV);
     CHECK(result[3].value == "/");
  }

   SECTION("Sequence 3"){
     Tokenizer t = Tokenizer("var blarp = 2; ");
     vector<Token> result = t.getTokens();

     REQUIRE(result.size() == 5);

     CHECK(result[0].type == TokenType::VAR);
     CHECK(result[1].type == TokenType::IDENTIFIER);
     CHECK(result[1].value == "blarp");
     CHECK(result[2].type == TokenType::ASSIGN);
     CHECK(result[3].type == TokenType::INT);
     CHECK(result[3].value == "2");
     CHECK(result[4].type == TokenType::EOL);
   }

   SECTION("Sequence 2"){
     Tokenizer t = Tokenizer("5   (( ** 123 \"213\" ");
     vector<Token> result = t.getTokens();
     REQUIRE(result.size() == 7);
     CHECK(result[0].type == TokenType::INT);
     CHECK(result[0].value == "5");
     CHECK(result[1].type == TokenType::LPAREN);
     CHECK(result[1].value == "(");
     CHECK(result[2].type == TokenType::LPAREN);
     CHECK(result[2].value == "(");
     CHECK(result[3].type == TokenType::MUL);
     CHECK(result[3].value == "*");
     CHECK(result[4].type == TokenType::MUL);
     CHECK(result[4].value == "*");
     CHECK(result[5].type == TokenType::INT);
     CHECK(result[5].value == "123");
     CHECK(result[6].type == TokenType::STRING);
     CHECK(result[6].value == "213");
  }
}

TEST_CASE( "Tokenizer exceptional scenarios", "Exceptions" )
{
   SECTION("Unexpected character"){
      Tokenizer t = Tokenizer("'");
      REQUIRE_THROWS_AS(t.getTokens(), TokenizerException);
   }


   SECTION("Unterminated string"){
      Tokenizer t = Tokenizer("\"asdas");
      REQUIRE_THROWS_AS(t.getTokens(), TokenizerException);

      t = Tokenizer("\"");
      REQUIRE_THROWS_AS(t.getTokens(), TokenizerException);
   }


}
