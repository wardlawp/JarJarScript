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

         ~Binary()
         {
            delete left;
            delete right;
         }

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

         ~Unary()
         {
            delete right;
         }

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

         ~Grouping()
         {
            delete exp;
         }
   };

   class Literal: public Expression
   {
      public:
         Literal(Object *val)
         {
            value = shared_ptr<Object>(val);
         };

         ~Literal(){}

         shared_ptr<Object>  value;
   };

   class Variable: public Expression
   {
      public:
         Variable(Token n) : name(n){ };
         ~Variable() {}

         Token name;
   };

   class Assign: public Expression
   {
      public:
         Assign(Token n, Expression * expression) : name(n)
         {
            exp = expression;
         }

         ~Assign()
         {
            delete exp;
         }

         Token name;
         Expression * exp;
   };
}
#endif /* SRC_AST_H_ */
