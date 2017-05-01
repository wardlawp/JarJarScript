#ifndef SRC_TOKENIZER_H
#define SRC_TOKENIZER_H

#include <stdio.h>
#include <algorithm>
#include <Token.h>
#include <TokenConstants.h>
#include <vector>
#include <Exceptions.h>


using namespace std;

namespace JarJar
{

   class Tokenizer
   {
      public:
         Tokenizer(string source);
         vector<Token> getTokens();

      private:
         string source;
         int line;
         int start;
         int current;
         vector<Token> result;

         bool atEnd();

         void addToken(TokenType type, string value = "");

         void scanToken();
         bool matchKeywords();
         void matchNumeric();
         bool whitespace(char c);
         void skipWhitespace();
         void parseString();
         bool matchMultiCharToken(TokenType t, string reperesentation);
         char peek(int rel);
         char snack();
   };
}

#endif
