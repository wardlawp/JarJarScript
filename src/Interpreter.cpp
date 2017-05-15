#include <Interpreter.h>

namespace JarJar
{

   Object * Interpreter::visitBinary(Binary * expr)
   {
      Object * left = visit(expr->left);
      Object * right = visit(expr->right);

      typeCheck(left,right, expr->op);

      switch (expr->op.type) {
         case TokenType::ADD :
            return left->operator+(right);
         case TokenType::SUB :
            return left->operator-(right);
         case TokenType::MUL :
            return left->operator*(right);
         case TokenType::DIV :
            return left->operator/(right);
         case TokenType::ASSIGN :
             return left->operator=(right);
         case TokenType::GT :
           return left->operator>(right);
        case TokenType::GTE :
           return left->operator>=(right);
        case TokenType::LT :
           return left->operator<(right);
        case TokenType::LTE :
            return left->operator<=(right);
        case TokenType::EQUALS :
           return left->operator==(right);
         default:
            throw InterpreterException("Binary operation " + getStringRepr(expr->op.type) + " not implemented");
      }
   }

   Object * Interpreter::visitUnary(Unary * expr)
   {
      Object * right = visit(expr->right);


      switch (expr->op.type) {
         case TokenType::SUB:
           return right->negate();
         case TokenType::NOT:
             return right->operator !();
        default:
           throw InterpreterException("Unary operation " + getStringRepr(expr->op.type) + " not implemented");
      }

   }

   Object * Interpreter::visitGrouping(Grouping * expr)
   {
      return visit(expr->exp);
   }

   Object * Interpreter::visitLiteral(Literal * expr)
   {
      return expr->value;
   }

   void Interpreter::typeCheck(Object * left, Object * right, Token t)
   {
      if(typeid(*left) != typeid(*right)){
         string leftStr = type(*left);
         string rightStr = type(*right);
         string msg = "Left (" + leftStr + ") and right (" + rightStr + ") operand types do not match";
         throw TypeMissMatchException(t, msg);
      }
   }

}
