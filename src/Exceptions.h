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

   class ParserException: TokenizerException {
      public:
         ParserException(const Token t, const string customMsg = "") : TokenizerException(t, customMsg){}
   };

   class ObjectMethodDoesNotExistException: runtime_error
   {
      public:
         ObjectMethodDoesNotExistException(const std::string& msg) : runtime_error(msg) {}
   };

   class TypeMissMatchException: TokenizerException
   {
      public:
         TypeMissMatchException(const Token t, const string customMsg = "") : TokenizerException(t, customMsg){}
   };

   class InterpreterException: runtime_error
   {
      public:
         InterpreterException(const std::string& msg) : runtime_error(msg) {}
   };
}

#endif
