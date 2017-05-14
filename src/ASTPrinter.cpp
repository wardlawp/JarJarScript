#include <ASTPrinter.h>

namespace JarJar {
   string ASTPrinter::wrap(Expression * e)
   {
      bool notGrouping = (typeid(*e) != typeid(Grouping));
      bool notLiteral = (typeid(*e) != typeid(Literal));

      if(notGrouping and notLiteral){
         return '(' + visit(e) + ')';
      } else
      {
         return visit(e);
      }
   }

   string ASTPrinter::visitBinary(Binary * expr)
   {
      string left = wrap(expr->left);
      string right = wrap(expr->right);
      return left + ' ' + expr->op.value + ' ' + right;
   }

   string ASTPrinter::visitUnary(Unary * expr)
   {
      return expr->op.value + " " + wrap(expr->right);
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
