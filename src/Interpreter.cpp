#include <Interpreter.h>

namespace JarJar
{

   void Interpreter::interpert(vector<Statement*> statements)
   {
      for(auto statement: statements)
      {
         try {
            visitStatement(statement);
         } catch (InterpreterException &e){
            //todo
            cout << e.what() << endl;
         }

      }
   }

   Object * Interpreter::visitBinary(Binary * expr)
   {
      Object * left = visitExpression(expr->left);
      Object * right = visitExpression(expr->right);

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
      Object * right = visitExpression(expr->right);


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
      return visitExpression(expr->exp);
   }

   Object * Interpreter::visitLiteral(Literal * expr)
   {
      return expr->value;
   }

   void Interpreter::visitPrintStatment(PrintStatment * statement)
   {
      cout << visitExpression(statement->expr)->toStr();
   }
   void Interpreter::visitExpressionStatment(ExpressionStatment * statement)
   {
      visitExpression(statement->expr);
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
