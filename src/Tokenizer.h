#include <stdio.h>
#include <algorithm>
#include <Token.h>
#include <vector>

//Temporary include
#include <iostream>

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
        void matchKeywords();
        void matchNumeric();
        bool matchMultiCharToken(TokenType t, string reperesentation);
        char peek(int rel);
        char snack();

        bool isNumeric(char c);


    public:
        Tokenizer(string source);
        vector<Token> getTokens();
    };
}
