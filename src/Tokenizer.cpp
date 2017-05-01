#include "Tokenizer.h"

namespace JarJar
{

   Tokenizer::Tokenizer(string source)
   {
      this->source = source;
      start = current = line = 0;
   }

   vector<Token> Tokenizer::getTokens()
   {
      result = vector<Token>();

      while (!atEnd()) {
         scanToken();
         start = current;
      }

      return result;
   }

   void Tokenizer::scanToken()
   {

      char curr = source[start];

      if (isdigit(curr)) {
         matchNumeric();
      } else if (curr == '"') {
         parseString();
      } else if (whitespace(curr)) {
         skipWhitespace();
      } else if (!matchKeywords()) {
         Token errorToken = Token(TokenType::ADD, source.substr(start), line);
         throw TokenizerException(errorToken, "Unrecognized Token.");
      }
   }

   bool Tokenizer::whitespace(char c)
   {
      return (c == ' ' or c == '\t');
   }

   void Tokenizer::skipWhitespace()
   {
      while (source[current] == ' ' or source[current] == '\t') {
         current++;
      }
   }

   void Tokenizer::parseString()
   {
      while (snack() != '"' and !atEnd());

      if(source[current] != '"'){
         Token errorToken = Token(TokenType::ADD, source.substr(start), line);
         throw TokenizerException(errorToken, "Unterminated string");
      }

      addToken(TokenType::STRING,
            source.substr(start + 1, current - start - 1));

      current++;
   }

   void Tokenizer::matchNumeric()
   {
      bool decimal = false;
      char next = snack();

      while (isdigit(next) or next == DECIMEL_DOT_REPR) {
         decimal = decimal ? true : next == DECIMEL_DOT_REPR;
         next = snack();
      }

      TokenType t = decimal ? TokenType::DECIMAL : TokenType::INT;

      addToken(t, source.substr(start, current - start));
   }

   bool Tokenizer::matchKeywords()
   {
      for (pair<TokenType, string> rule : typesToString) {
         if (matchMultiCharToken(rule.first, rule.second))
            return true;
      }

      return false;
   }

   bool Tokenizer::matchMultiCharToken(TokenType t, string representation)
   {

      string curr = source.substr(current, 1);
      while (curr == representation.substr(0, curr.length())) {

         if (curr == representation) {
            current += curr.length();
            addToken(t, representation);
            return true;
         }

         curr += peek(curr.length());
      }

      return false;
   }

   char Tokenizer::snack()
   {
      if (!atEnd()) {
         current += 1;
         return source[current];
      }

      return ' ';
   }

   char Tokenizer::peek(int rel)
   {
      int pos = current + rel;
      if (pos > source.length()) {
         return ' ';
      }

      return source[pos];
   }

   void Tokenizer::addToken(TokenType type, string value)
   {
      result.push_back(Token(type, value, line));
   }

   bool Tokenizer::atEnd()
   {
      return (current >= source.length());
   }
}
