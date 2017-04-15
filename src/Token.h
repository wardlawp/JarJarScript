#include <string>
using namespace std;
namespace JarJar {

    enum TokenType {
        //Operators
        ASSIGN, EQUALS, ADD, SUB, MUL, DIV,

        //Primitives
        BOOL, INT, DECIMEL, STRING,

        //Keywords
        AND, OR, IF, ELSE, BREAK, WHILE, FOR
    };

    class Token {
        public:
            static const string TRUE;
            TokenType type;
            string text;
            int line;
            string value;

            Token(TokenType type, string text, string value, int line);
    };

}
