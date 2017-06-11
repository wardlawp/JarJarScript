#ifndef SRC_AST_H_
#define SRC_AST_H_

#include <TokenConstants.h>
#include <Object.h>
#include <Token.h>


namespace JarJar
{
   class Expression
   {
      public:
         virtual ~Expression() {}
   };

   class Binary: public Expression
   {
      public:
         Binary(Expression * l, Token o, Expression * r) :op(o)
         {
            left = l;
            right = r;
         };

         Expression * left;
         Token op;
         Expression * right;
   };

   class Unary: public Expression
   {
      public:
         Unary(Token o, Expression * r) : op(o)
         {
            right = r;
         };

         Token op;
         Expression * right;
   };

   class Grouping: public Expression
   {
      public:
         Expression * exp;
         Grouping(Expression * expression)
         {
            exp = expression;
         }
   };

   class Literal: public Expression
   {
      public:
         Literal(Object *val)
         {
            value = val;
         };

         Object * value;
   };

   class Variable: public Expression
   {
      public:
         Variable(Token n) : name(n){ };

         Token name;
   };

   class Assign: public Expression
   {
      public:
         Assign(Token n, Expression * expression) : name(n)
         {
            exp = expression;
         }

         Token name;
         Expression * exp;
   };
}
#endif /* SRC_AST_H_ */
