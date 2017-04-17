#include <catch.hpp>
#include <Token.h>

using namespace JarJar;

TEST_CASE( "Token parses input to int", "int parse" ) {
    Token t = Token(TokenType::INT, "123", 0);
    REQUIRE( t.getIntVal() == 123);

    //TODO test exception
}

TEST_CASE( "Token parses input to double", "int parse" ) {
    Token t = Token(TokenType::INT, "123.23", 0);
    REQUIRE( t.getDoubleVal() == 123.23);

    //TODO test exception
}
