#include <catch.hpp>
#include <Token.h>

using namespace JarJar;

TEST_CASE( "Token inputs to correct type", "Token Value Parse" ) {

    SECTION("Int parse"){
        Token t = Token(TokenType::INT, "123", 0);
        REQUIRE( t.getIntVal() == 123);
    }

    SECTION("Double parse"){
        Token t = Token(TokenType::DECIMAL, "123.23", 0);
        REQUIRE( t.getDoubleVal() == 123.23);
    }

    SECTION("String parse"){
        Token t = Token(TokenType::STRING, " hello ", 0);
        REQUIRE( t.getStringVal() == " hello ");
    }

    SECTION("Bool parse"){
       Token t = Token(TokenType::BOOL, "na", 0);
       REQUIRE( t.getBoolVal() == false);

       t = Token(TokenType::BOOL, "ya", 0);
       REQUIRE( t.getBoolVal() == true);
   }
}
