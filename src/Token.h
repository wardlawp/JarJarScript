#include <string>
#include <vector>
#include <map>

using namespace std;

namespace JarJar {

    enum TokenType {
        //Operators
        ASSIGN, EQUALS, NOT_EQUALS, LT, GT, LTE, GTE, ADD, SUB, MUL, DIV, NEGATE,
        LPAREN, RPAREN,

        //Primitives
        BOOL, INT, DECIMAL, STRING, NADA,

        //Keywords
        AND, OR, IF, ELSE, BREAK, WHILE, FOR
    };


    class Token {
    private:
        string value;

    public:
        static vector<pair<TokenType, string>> typesToString;
        static map<bool, string> boolsToString;
        TokenType type;
        int line;

        int getIntVal();
        double getDoubleVal();
        string getStringVal();
        bool getBoolVal();


        Token(TokenType type, string value, int line);
    };

}
