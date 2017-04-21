#include "Token.h"
#include <iostream>

using namespace JarJar;
using namespace std;

namespace JarJar
{

   int Token::getIntVal()
   {
      return atoi(value.c_str());
   }

   double Token::getDoubleVal()
   {
      return atof(value.c_str());
   }

   string Token::getStringVal()
   {
      return value;
   }

   bool Token::getBoolVal()
   {
      for (pair<bool, string> const &rule : boolsToString) {
         if (rule.second == value) {
            return rule.first;
         }
      }

      return false; //TODO throw exception
   }

   Token::Token(TokenType t, string v, int l)
   {
      type = t;
      value = v;
      line = l;
   }
}
