#include <Exceptions.h>

namespace JarJar {
   TokenizerException::TokenizerException(const Token t, const string customMsg) : runtime_error(customMsg)
   {
      msg = '"' + t.value + "\" at line " + to_string(t.line) + ".\n";

      if (customMsg != "") {
         msg = customMsg + '\n' + msg;
      }
   }

   ParserException::ParserException(const Token t, const string customMsg) 
      : TokenizerException(t, customMsg) {}

   TypeMissMatchException::TypeMissMatchException(const Token t, const string customMsg) 
      : TokenizerException(t, customMsg) {}

   LiteralConversionException::LiteralConversionException(const Token t, const string customMsg) 
      : TokenizerException(t, customMsg) {}
}