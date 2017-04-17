#include <string>
#include <vector>

using namespace std;

namespace JarJar {

    enum TokenType {
        //Operators
        ASSIGN, EQUALS, NOT_EQUALS, LT, GT, LTE, GTE, ADD, SUB, MUL, DIV, NEGATE,
        LPAREN, RPAREN,

        //Primitives
        BOOL, INT, DECIMEL, STRING,

        //Keywords
        AND, OR, IF, ELSE, BREAK, WHILE, FOR
    };


    class Token {
        public:
            static vector<pair<TokenType, string>> typeToString;
            TokenType type;
            string text;
            int line;
            string value;

            Token(TokenType type, string text, string value, int line);
    };

}
