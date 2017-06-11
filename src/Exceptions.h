#ifndef SRC_EXCEPTIONS_H
#define SRC_EXCEPTIONS_H

#include <exception>
#include <Token.h>
#include <string>

using namespace std;

namespace JarJar {
   class TokenizerException : public runtime_error {
      private:
         string msg;
      public:
         TokenizerException(const Token t, const string customMsg = ""): runtime_error(customMsg)
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

   class ParserException: public TokenizerException {
      public:
         ParserException(const Token t, const string customMsg = "") : TokenizerException(t, customMsg){}
   };

   class ObjectMethodDoesNotExistException: public runtime_error
   {
      public:
         ObjectMethodDoesNotExistException(const string& msg) : runtime_error(msg) {}
   };

   class TypeMissMatchException: public TokenizerException
   {
      public:
         TypeMissMatchException(const Token t, const string customMsg = "") : TokenizerException(t, customMsg){}
   };

   class DivideByZeroException:  public runtime_error
   {
      public:
         DivideByZeroException(const string& msg = "") : runtime_error(msg) {}
   };

   class InterpreterException: public runtime_error
   {
      public:
         InterpreterException(const string& msg) : runtime_error(msg) {}
   };

   class VariableNotDefinedException: public runtime_error
   {
      public:
         VariableNotDefinedException(const string& msg) : runtime_error(msg) {}
   };
}

#endif
