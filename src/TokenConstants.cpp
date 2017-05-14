#include <TokenConstants.h>

namespace JarJar {
   const string getStringRepr(const TokenType & t)
      {
         for (pair<TokenType, string> match : typesToString) {
            if (match.first  == t){
               return match.second;
            }
         }

         throw runtime_error("Could not find string representation");
      }
}
