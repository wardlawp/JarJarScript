#ifndef SRC_INTERPRETER_H_
#define SRC_INTERPRETER_H_

#include <Visitors.h>
#include <Object.h>
#include <AST.h>
#include <Token.h>
#include <Exceptions.h>
#include <TokenConstants.h>

namespace JarJar
{

   class Interpreter : public Visitor<Object*>
   {
      private:
         void typeCheck(Object * left, Object * right, Token t);
      public:
         Interpreter() {} ;
         virtual ~Interpreter();
         virtual Object * visitBinary(Binary * expr);
         virtual Object * visitUnary(Unary * expr);
         virtual Object * visitGrouping(Grouping * expr);
         virtual Object * visitLiteral(Literal * expr);
   };

} /* namespace JarJar */

#endif /* SRC_INTERPRETER_H_ */
