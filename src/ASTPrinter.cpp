#include <ASTPrinter.h>

namespace JarJar {
   string ASTPrinter::wrap(Expression * e)
   {
      bool notGrouping = (typeid(*e) != typeid(Grouping));
      bool notLiteral = (typeid(*e) != typeid(Literal));

      if(notGrouping && notLiteral){
         return '(' + visitExpression(e) + ')';
      } else
      {
         return visitExpression(e);
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
      return "(" + visitExpression(expr->exp) + ")";
   }

   string ASTPrinter::visitLiteral(Literal * expr)
   {
      return expr->value->toStr();
   }

   string ASTPrinter::visitVariable(Variable * expr)
   {
      return "Reference to variable " + expr->name.value;
   }

   string ASTPrinter::visitAssign(Assign * expr)
   {
      return "Assignment of variable " + expr->name.value;
   }

   string ASTPrinter::visitLogical(Logical * expr)
   {
      return visitExpression(expr->left) + " " + getStringRepr(expr->t) + " " + visitExpression(expr->left);
   }

   string ASTPrinter::visitCall(Call * expr)
   {
      return "Function call to " + visitExpression(expr->callee);
   }
}
