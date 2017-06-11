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
#include <Statement.h>
#include <iostream>
#include <vector>
#include <Environment.h>

using namespace std;

namespace JarJar
{

   class Interpreter : public ExperssionVisitor<Object*>, public StatementVisitor
   {
      private:
         void typeCheck(Object * left, Object * right, Token t);
         Environment env;
      public:
         Interpreter()
         {
            env = Environment();
         };

         void interpert(vector<Statement*> statements);

         /* ExperssionVisitor<Object*> virtual methods */
         virtual Object * visitBinary(Binary * expr);
         virtual Object * visitUnary(Unary * expr);
         virtual Object * visitGrouping(Grouping * expr);
         virtual Object * visitLiteral(Literal * expr);
         virtual Object * visitVariable(Variable * expr);

         /* StatementVisitor virtual methods */

         virtual void visitPrintStatment(PrintStatment * statment);
         virtual void visitExpressionStatment(ExpressionStatment * statment);
         virtual void visitVariableStatment(VariableStatment * statement);

         /* Public test method for accessing private env safely */
         Object * getVar(string name);
   };



} /* namespace JarJar */

#endif /* SRC_INTERPRETER_H_ */
