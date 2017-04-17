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
          this->start = this->current;
          scanToken();
      }

      return this->result;
  }

  void Tokenizer::scanToken()
  {

      matchToken();


      this->current++;
  }


  void Tokenizer::matchToken()
  {
      vector<pair<TokenType, string>> m = Token::typeToString;

      string curr = source.substr(current, 1);

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

  char Tokenizer::peek(int rel)
  {
      int pos = current + rel;
      if(pos  > source.length()){
          return ' ';
      }

      return source[pos];
  }



  void Tokenizer::addToken(TokenType type)
  {
      result.push_back(Token(type, "", "", line));
  }

  bool Tokenizer::atEnd()
  {
      return (this->current > this->source.length());
  }
}
