#include <Statement.h>
#include <typeinfo>

#ifndef SRC_STMT_VISITOR_H_
#define SRC_STMT_VISITOR_H_

namespace JarJar {

   class StatementVisitor {
      public:
         virtual ~StatementVisitor() {}

         void visitStatement(Statement * s)
         {
            if(typeid(*s) == typeid(PrintStatment)){
               visitPrintStatment(dynamic_cast<PrintStatment*>(s));
            } else if (typeid(*s) == typeid(ExpressionStatment)){
               visitExpressionStatment(dynamic_cast<ExpressionStatment*>(s));
            } else if (typeid(*s) == typeid(VariableStatment)){
               visitVariableStatment(dynamic_cast<VariableStatment*>(s));
            } else if (typeid(*s) == typeid(Block)){
               visitBlock(dynamic_cast<Block*>(s));
            } else if (typeid(*s) == typeid(IfStatement)){
               visitIfStatement(dynamic_cast<IfStatement*>(s));
            } else if (typeid(*s) == typeid(WhileStatement)){
               visitWhileStatement(dynamic_cast<WhileStatement*>(s));
            } else if (typeid(*s) == typeid(FunctionDeclaration)) {
               visitFunctionDeclaration(dynamic_cast<FunctionDeclaration*>(s));
            } else if (typeid(*s) == typeid(ReturnSatatment)) {
               visitReturnStatement(dynamic_cast<ReturnSatatment*>(s));
            }  else {
               throw invalid_argument("Statement type not supported");
            }
         }


         virtual void visitPrintStatment(PrintStatment * statment) = 0;
         virtual void visitExpressionStatment(ExpressionStatment * statment) = 0;
         virtual void visitVariableStatment(VariableStatment * statement) = 0;
         virtual void visitBlock(Block * statement) = 0;
         virtual void visitIfStatement(IfStatement * statement) = 0;
         virtual void visitWhileStatement(WhileStatement * statement) = 0;
         virtual void visitFunctionDeclaration(FunctionDeclaration * statement) = 0;
         virtual void visitReturnStatement(ReturnSatatment * statement) = 0;
   };
}

#endif /* SRC_STMT_VISITOR_H_ */
