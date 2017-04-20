#include <stdio.h>
#include <algorithm>
#include <Token.h>
#include <vector>
#include <functional>


using namespace std;

namespace JarJar {

    class Tokenizer {
    
    private:
        string source;
        int line;
        int start;
        int current;

        bool atEnd();

        void addToken(TokenType type, string value = "");
        vector<Token> result;

        void scanToken();
        bool matchKeywords();
        void matchNumeric();
        bool whitespace(char c);
        void skipWhitespace();
        void parseString();
        bool matchMultiCharToken(TokenType t, string reperesentation);
        char peek(int rel);
        char snack();

        bool isNumeric(char c);


    public:
        Tokenizer(string source);
        vector<Token> getTokens();
    };
}
