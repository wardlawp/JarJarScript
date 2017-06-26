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

   Object * Interpreter::visitAssign(Assign * expr)
   {
      Object * value = visitExpression(expr->exp);

      env->assign(expr->name.value, value);

      return value;
   }

   Object * Interpreter::visitGrouping(Grouping * expr)
   {
      return visitExpression(expr->exp);
   }

   Object * Interpreter::visitLiteral(Literal * expr)
   {
      return expr->value;
   }

   Object * Interpreter::visitVariable(Variable * expr)
   {
      return env->get(expr->name.value);
   }

   void Interpreter::visitPrintStatment(PrintStatment * statement)
   {
      //TODO need to delete here for anything produced by statement OTHER than from a Literal
      Object* result = visitExpression(statement->expr);
      //short term workaround
      output->push_back(result->toStr());
   }

   void Interpreter::visitExpressionStatment(ExpressionStatment * statement)
   {
      visitExpression(statement->expr);
   }

   void Interpreter::visitVariableStatment(VariableStatment * statement)
   {
      string name = statement->name.value;
      if(statement->expr != 0)
      {
         env->define(name, visitExpression(statement->expr));
      } else {
         env->define(name, 0);
      }
   }

   void Interpreter::visitBlock(Block * statement){
      //TODO memory management on block destruction
      //TODO handle error scenario and correctly set env back to previous
      previous = env;

      env = new Environment(previous);

      for(auto s: statement->statements)
      {
         visitStatement(s);
      }

      delete env;
      env = previous;
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

   Object * Interpreter::getVar(string name)
   {
      return env->get(name);
   }

}
