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
#include <Return.h>

using namespace std;

namespace JarJar
{
   typedef std::shared_ptr<JarJar::Environment> RefEnvironment;

   class Interpreter : public ExperssionVisitor<SObject>, public StatementVisitor
   {
      public:
         Interpreter(queue<string> * op = nullptr);

         void interpert(vector<shared_ptr<Statement>> statements);

         /* ExperssionVisitor<Object*> virtual methods */
         virtual SObject visitBinary(Binary* expr);
         virtual SObject visitUnary(Unary* expr);
         virtual SObject visitGrouping(Grouping* expr);
         virtual SObject visitLiteral(Literal* expr);
         virtual SObject visitVariable(Variable* expr);
         virtual SObject visitAssign(Assign* expr);
         virtual SObject visitLogical(Logical * expr);
         virtual SObject visitCall(Call * expr);

         /* StatementVisitor virtual methods */
         virtual void visitPrintStatment(PrintStatment* statment);
         virtual void visitExpressionStatment(ExpressionStatment* statment);
         virtual void visitVariableStatment(VariableStatment* statement);
         virtual void visitBlock(Block* statement);
         virtual void visitIfStatement(IfStatement * statement);
         virtual void visitWhileStatement(WhileStatement * statement);
         virtual void visitFunctionDeclaration(FunctionDeclaration * statement);
         virtual void visitReturnStatement(ReturnSatatment* statement);

         void executeBlock(Block* statement, RefEnvironment env);

         /* Public test method for accessing private env safely */
         SObject getVar(string name);

         RefEnvironment global;

   private:
      void initStdLibFunctions();
      void typeCheck(Object* left, Object* right, Token t);
      RefEnvironment env;
      queue<string> * output;
   };



} /* namespace JarJar */

#endif /* SRC_INTERPRETER_H_ */
