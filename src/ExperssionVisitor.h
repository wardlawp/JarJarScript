#include <AST.h>
#include <typeinfo>

#ifndef SRC_VISITORS_H_
#define SRC_VISITORS_H_

namespace JarJar {

   template<class R>
   class ExperssionVisitor {
      public:
         virtual ~ExperssionVisitor() {}

         R visitExpression(Expression * e)
         {
            //todo refactor
            if(typeid(*e) == typeid(Binary)){
               return visitBinary(dynamic_cast<Binary*>(e));
            } else if (typeid(*e) == typeid(Unary)){
               return visitUnary(dynamic_cast<Unary*>(e));
            } else if (typeid(*e) == typeid(Grouping)){
               return visitGrouping(dynamic_cast<Grouping*>(e));
            } else if (typeid(*e) == typeid(Literal)){
               return visitLiteral(dynamic_cast<Literal*>(e));
            } else if (typeid(*e) == typeid(Variable)){
               return visitVariable(dynamic_cast<Variable*>(e));
            } else if (typeid(*e) == typeid(Assign)){
               return visitAssign(dynamic_cast<Assign*>(e));
            }else if (typeid(*e) == typeid(Logical)){
               return visitLogical(dynamic_cast<Logical*>(e));
            }

            throw invalid_argument("Expression type not supported");
         }


         virtual R visitBinary(Binary * expr) = 0;
         virtual R visitUnary(Unary * expr) = 0;
         virtual R visitGrouping(Grouping * expr) = 0;
         virtual R visitLiteral(Literal * expr) = 0;
         virtual R visitVariable(Variable * expr) = 0;
         virtual R visitAssign(Assign * expr) = 0;
         virtual R visitLogical(Logical * expr) = 0;
   };
}

#endif /* SRC_VISITORS_H_ */
