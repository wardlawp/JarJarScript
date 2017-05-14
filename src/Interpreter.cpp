/*
 * Interpreter.cpp
 *
 *  Created on: May 6, 2017
 *      Author: wardlaw
 */

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
         default:
            throw InterpreterException("Binary operation " + getStringRepr(expr->op.type) + " not implemented");
      }
   }

   Object * Interpreter::visitUnary(Unary * expr)
   {
      Object * right = visit(expr->right);

      if(expr->op.type != TokenType::SUB){
         throw InterpreterException("Unary operation " + getStringRepr(expr->op.type) + " not implemented");
      }

      return right->negate();
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
      if(typeid(left) != typeid(right)){
         throw TypeMissMatchException(t, "Left and right operand types do not match");
      }
   }

}
