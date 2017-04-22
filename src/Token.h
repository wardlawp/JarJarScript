#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include <string>
#include <TokenConstants.h>
using namespace std;

namespace JarJar
{
   class Token
   {
      public:
         TokenType type;
         int line;
         string value;

         Token(TokenType type, string value, int line);

         int getIntVal();
         double getDoubleVal();
         string getStringVal();
         bool getBoolVal();
   };

}

#endif
