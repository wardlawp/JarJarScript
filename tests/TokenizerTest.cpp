#include <catch.hpp>
#include <Tokenizer.h>

using namespace JarJar;
using namespace std;


#define TOKEN_CHECK(str, T) {\
        SECTION("Scan " str " operator"){ \
            Tokenizer t = Tokenizer(str); \
            vector<Token> result = t.getTokens(); \
            REQUIRE(result.size() == 1); \
            REQUIRE(result[0].type == T); \
        } \
    }

//- Tokenizer can scan operators +,-, /,*, =, !, ==, !=, >, <, >=, <=, (, )
TEST_CASE( "Tokenizer scans operators", "scan operators" ) {
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
TEST_CASE( "Tokenizer scans keywords", "scan operators" ) {
    TOKEN_CHECK("and", TokenType::AND);
    TOKEN_CHECK("or", TokenType::OR);
    TOKEN_CHECK("ifsa", TokenType::IF);
    TOKEN_CHECK("elsa", TokenType::ELSE);
    TOKEN_CHECK("break", TokenType::BREAK);
    TOKEN_CHECK("while", TokenType::WHILE);
    TOKEN_CHECK("for", TokenType::FOR);
}


//- Tokenizer can scan primitives string, int, double, bool, null
TEST_CASE( "Tokenizer scans primitives", "scan operators" ) {
    SECTION("Scan int"){
        Tokenizer t = Tokenizer("123");
        vector<Token> result = t.getTokens();

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == TokenType::INT);
        REQUIRE(result[0].getIntVal() == 123);
    }

    SECTION("Scan decimal"){
        Tokenizer t = Tokenizer("123.23");
        vector<Token> result = t.getTokens();

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == TokenType::DECIMAL);
        REQUIRE(result[0].getDoubleVal() == 123.23);
    }
}
// TODO
//- Tokenizer differentiates certain operators
//- Tokenizer differentiates keywords from strings
//- Tokenizer reads sequences
//- Tokenizer counts lines
