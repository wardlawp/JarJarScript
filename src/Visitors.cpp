#include <Visitors.h>


namespace JarJar {

   template<class T>
   T Visitor<T>::visit(Expression  * e)
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

   string ASTPrinter::visitBinary(Binary * expr)
   {
      string left = visit(expr->left);
      string right = visit(expr->right);
      return left + ' ' + expr->op.value + ' ' + right;
   }

   string ASTPrinter::visitUnary(Unary * expr)
   {
      return expr->op.value + " " + visit(expr->right);
   }

   string ASTPrinter::visitGrouping(Grouping * expr)
   {
      return "(" + visit(expr->exp) + ")";
   }

   string ASTPrinter::visitLiteral(Literal * expr)
   {
      return expr->value->toStr();
   }
}
