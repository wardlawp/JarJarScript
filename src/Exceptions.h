#ifndef SRC_EXCEPTIONS_H
#define SRC_EXCEPTIONS_H

#include <exception>
#include <Token.h>
#include <string>

using namespace std;

namespace JarJar {
   
   //Forward Declaration
   class Token;

   class TokenizerException : public runtime_error {
      protected:
         string msg;
      public:
         TokenizerException(): runtime_error("") {}
         TokenizerException(const Token t, const string customMsg = "");


         virtual const char* what() const
         {
            return msg.c_str();
         }
   };

   class ParserException: public TokenizerException {
      public:
         ParserException() = default;
         ParserException(const Token t, const string customMsg);
   };

   class ObjectMethodDoesNotExistException: public runtime_error
   {
      public:
         ObjectMethodDoesNotExistException(const string& msg) : runtime_error(msg) {}
   };

   class TypeMissMatchException: public TokenizerException
   {
      public:
         TypeMissMatchException(const Token t, const string customMsg = "");
   };

   class LiteralConversionException : public TokenizerException
   {
      public:
         LiteralConversionException(const Token t, const string customMsg = "");
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
