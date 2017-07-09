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
            //TODO refactor
            if(typeid(*s) == typeid(PrintStatment)){
               visitPrintStatment(dynamic_cast<PrintStatment*>(s));
               return;
            } else if (typeid(*s) == typeid(ExpressionStatment)){
               visitExpressionStatment(dynamic_cast<ExpressionStatment*>(s));
               return ;
            } else if (typeid(*s) == typeid(VariableStatment)){
               visitVariableStatment(dynamic_cast<VariableStatment*>(s));
               return ;
            } else if (typeid(*s) == typeid(Block)){
               visitBlock(dynamic_cast<Block*>(s));
               return ;
            } else if (typeid(*s) == typeid(IfStatement)){
               visitIfStatement(dynamic_cast<IfStatement*>(s));
               return ;
            }

            throw invalid_argument("Statement type not supported");
         }


         virtual void visitPrintStatment(PrintStatment * statment) = 0;
         virtual void visitExpressionStatment(ExpressionStatment * statment) = 0;
         virtual void visitVariableStatment(VariableStatment * statement) = 0;
         virtual void visitBlock(Block * statement) = 0;
         virtual void visitIfStatement(IfStatement * statement) = 0;
   };
}

#endif /* SRC_STMT_VISITOR_H_ */
