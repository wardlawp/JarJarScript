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

         Token(TokenType type, string value, int line);

         int getIntVal();
         double getDoubleVal();
         string getStringVal();
         bool getBoolVal();

         private:
            string value;
   };

}
