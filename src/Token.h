#include <string>
#include <vector>

using namespace std;

namespace JarJar {

    enum TokenType {
        //Operators
        ASSIGN, EQUALS, NOT_EQUALS, LT, GT, LTE, GTE, ADD, SUB, MUL, DIV, NEGATE,
        LPAREN, RPAREN,

        //Primitives
        BOOL, INT, DECIMAL, STRING,

        //Keywords
        AND, OR, IF, ELSE, BREAK, WHILE, FOR
    };


    class Token {
    private:
        string value;

    public:
        static vector<pair<TokenType, string>> typeToString;
        TokenType type;
        int line;

        int getIntVal();
        double getDoubleVal();


        Token(TokenType type, string value, int line);
    };

}
