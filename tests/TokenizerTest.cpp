#include <catch.hpp>
#include <Tokenizer.h>

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
   TOKEN_CHECK("!", TokenType::NEGATE);
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

      CHECK(result[3].type == TokenType::NEGATE);

      CHECK(result[4].type == TokenType::DECIMAL);
      CHECK(result[4].getDoubleVal() == 4.123);
   }
}
