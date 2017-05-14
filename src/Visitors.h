#include <AST.h>
#include <typeinfo>

#ifndef SRC_VISITORS_H_
#define SRC_VISITORS_H_

namespace JarJar {

   template<class R>
   class Visitor {
      public:
         virtual ~Visitor() {}

         R visit(Expression * e)
         {
            if(typeid(*e) == typeid(Binary)){
               return visitBinary(dynamic_cast<Binary*>(e));
            } else if (typeid(*e) == typeid(Unary)){
               return visitUnary(dynamic_cast<Unary*>(e));
            } else if (typeid(*e) == typeid(Grouping)){
               return visitGrouping(dynamic_cast<Grouping*>(e));
            } else if (typeid(*e) == typeid(Literal)){
               return visitLiteral(dynamic_cast<Literal*>(e));
            }
         }


         virtual R visitBinary(Binary * expr) = 0;
         virtual R visitUnary(Unary * expr) = 0;
         virtual R visitGrouping(Grouping * expr) = 0;
         virtual R visitLiteral(Literal * expr) = 0;
   };

   class ASTPrinter : public Visitor<string> {
      public:
         virtual string visitBinary(Binary * expr);
         virtual string visitUnary(Unary * expr);
         virtual string visitGrouping(Grouping * expr);
         virtual string visitLiteral(Literal * expr);

      private:
         string wrap(Expression * e);
   };
}

#endif /* SRC_VISITORS_H_ */
