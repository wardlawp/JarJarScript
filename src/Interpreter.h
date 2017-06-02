#ifndef SRC_INTERPRETER_H_
#define SRC_INTERPRETER_H_

#include <Object.h>
#include <AST.h>
#include <Token.h>
#include <Exceptions.h>
#include <ExperssionVisitor.h>
#include <TokenConstants.h>
#include <typeinfo>
#include <StatementVisitor.h>
#include <iostream>

namespace JarJar
{

   class Interpreter : public ExperssionVisitor<Object*>, public StatementVisitor
   {
      private:
         void typeCheck(Object * left, Object * right, Token t);
      public:
         Interpreter() {} ;

         /* ExperssionVisitor<Object*> virtual methods */
         virtual Object * visitBinary(Binary * expr);
         virtual Object * visitUnary(Unary * expr);
         virtual Object * visitGrouping(Grouping * expr);
         virtual Object * visitLiteral(Literal * expr);

         /* StatementVisitor virtual methods */

         virtual void visitPrintStatment(PrintStatment * statment);
         virtual void visitExpressionStatment(ExpressionStatment * statment);

   };



} /* namespace JarJar */

#endif /* SRC_INTERPRETER_H_ */
