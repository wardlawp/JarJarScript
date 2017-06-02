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
               return;
            } else if (typeid(*s) == typeid(ExpressionStatment)){
               visitExpressionStatment(dynamic_cast<ExpressionStatment*>(s));
               return ;
            }

            throw invalid_argument("Statement type not supported");
         }


         virtual void visitPrintStatment(PrintStatment * statment) = 0;
         virtual void visitExpressionStatment(ExpressionStatment * statment) = 0;
   };
}

#endif /* SRC_STMT_VISITOR_H_ */
