#include "Token.h"

using namespace JarJar;
using namespace std;

namespace JarJar
{

   int Token::getIntVal()
   {
      if (type != TokenType::INT) {
         throw LiteralConversionException(*this, "Token cannot be converted to int val");
      }

      return atoi(value.c_str());
   }

   double Token::getDoubleVal()
   {
      if (type != TokenType::DECIMAL) {
         throw LiteralConversionException(*this, "Token cannot be converted to double val");
      }

      return atof(value.c_str());
   }

   string Token::getStringVal()
   {
      return value;
   }

   bool Token::getBoolVal()
   {
      if (type != TokenType::BOOL) {
         throw LiteralConversionException(*this, "Token cannot be converted to bool val");
      }

      for (pair<bool, string> const &rule : boolsToString) {
         if (rule.second == value) {
            return rule.first;
         }
      }

      throw LiteralConversionException(*this, "Token bool value invalid");
   }

   Token::Token(TokenType t, string v, int l)
   {
      type = t;
      value = v;
      line = l;
   }
}
