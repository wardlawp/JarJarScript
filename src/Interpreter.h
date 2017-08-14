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
#include <queue>
#include <Environment.h>
#include <Typedefs.h>
#include <memory>
#include <Function.h>

using namespace std;

namespace JarJar
{

   class Interpreter : public ExperssionVisitor<SafeObject>, public StatementVisitor
   {
      private:
         void typeCheck(Object* left, Object* right, Token t);
         Environment * env;
         queue<string> * output;
      public:
         Environment * global;
         Interpreter(queue<string> * op = nullptr)
         {
            output = op;
            global = new Environment();
            env = global;
         };

         ~Interpreter()
         {
            delete env;
         }

         void interpert(vector<shared_ptr<Statement>> statements);

         /* ExperssionVisitor<Object*> virtual methods */
         virtual SafeObject visitBinary(Binary* expr);
         virtual SafeObject visitUnary(Unary* expr);
         virtual SafeObject visitGrouping(Grouping* expr);
         virtual SafeObject visitLiteral(Literal* expr);
         virtual SafeObject visitVariable(Variable* expr);
         virtual SafeObject visitAssign(Assign* expr);
         virtual SafeObject visitLogical(Logical * expr);
         virtual SafeObject visitCall(Call * expr);

         /* StatementVisitor virtual methods */

         virtual void visitPrintStatment(PrintStatment* statment);
         virtual void visitExpressionStatment(ExpressionStatment* statment);
         virtual void visitVariableStatment(VariableStatment* statement);
         virtual void visitBlock(Block* statement);
         virtual void visitIfStatement(IfStatement * statement);
         virtual void visitWhileStatement(WhileStatement * statement);
         virtual void visitFunctionDeclaration(FunctionDeclaration * statement);

         void executeBlock(Block* statement, Environment* env);

         /* Public test method for accessing private env safely */
         SafeObject getVar(string name);
   };



} /* namespace JarJar */

#endif /* SRC_INTERPRETER_H_ */
