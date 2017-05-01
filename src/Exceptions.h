#ifndef SRC_EXCEPTIONS_H
#define SRC_EXCEPTIONS_H

#include <exception>
#include <Token.h>
#include <string>

using namespace std;

namespace JarJar {
   class TokenizerException : exception {
      private:
         string msg;
      public:
         TokenizerException(const Token t, const string customMsg = "")
         {
            msg = '"'+ t.value + "\" at line " + to_string(t.line) + ".\n";

            if(customMsg!= ""){
               msg = customMsg + '\n' + msg;
            }

         }

         const char* what()
         {
            return msg.c_str();
         }
   };

}

#endif
