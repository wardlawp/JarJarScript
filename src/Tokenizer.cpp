#include "Tokenizer.h"

namespace JarJar {

  Tokenizer::Tokenizer(string source)
  {
    this->source = source;
    start = current = line = 0;
  }

  vector<Token> Tokenizer::getTokens()
  {
      this->result = vector<Token>();

      while(!atEnd())
      {
          scanToken();
          this->start = this->current;
      }

      return this->result;
  }

  void Tokenizer::scanToken()
  {

      char curr = source[start];

      if(isNumeric(curr)){
          matchNumeric();
      } else if(curr == '"') {
          parseString();
      }
      else {
          matchKeywords();
      }

      //TODO unrecognised token exception here
  }

  void Tokenizer::parseString()
  {
      while(snack() != '"' and !atEnd());

      addToken(TokenType::STRING, source.substr(start + 1, current -1));

      current++;
  }

  void Tokenizer::matchNumeric()
  {

      bool decimal =  false;
      char next = snack();

      while(isNumeric(next) or next == '.'){ //TODO refactor dot
          decimal = decimal? true: next == '.';
          next = snack();
      }

      TokenType t = decimal? TokenType::DECIMAL: TokenType::INT;

      addToken(t, source.substr(start, current));
  }

  bool Tokenizer::isNumeric(char c)
  {

      return (c <=  '9' && c >= '0');
  }

  void Tokenizer::matchKeywords()
  {
      vector<pair<TokenType, string>> m = Token::typesToString;

      string curr = source.substr(start, 1);

      for(pair<TokenType, string> rule: m)
      {
          if(matchMultiCharToken(rule.first, rule.second)) return;

          if(curr == rule.second){
              current +=1;
              addToken(rule.first);
              continue;
          }
      }
  }

  bool Tokenizer::matchMultiCharToken(TokenType t, string representation)
  {
      if(representation.length() > 1){
          string curr = source.substr(current, 1);
          while(curr == representation.substr(0, curr.length())){

              curr += peek(curr.length());

              if(curr == representation){
                  current+= curr.length();
                  addToken(t);
                  return true;
              }
          }
      }

      return false;
  }

  char Tokenizer::snack()
  {
      if(!atEnd())
      {
          current +=1;
          return source[current];
      }

      return ' ';
  }

  char Tokenizer::peek(int rel)
  {
      int pos = current + rel;
      if(pos  > source.length()){
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
      return (this->start >= this->source.length());
  }
}
