#ifndef SRC_AST_H_
#define SRC_AST_H_

#include <TokenConstants.h>
#include <Object.h>
#include <Token.h>


namespace JarJar
{
   template<class T>
   class Visitor;

   class Expression
   {
      public:
         virtual ~Expression() {}
         template<class T>
         T accept(Visitor<T> * visitor)
         {
               return visitor->visit(this);
         }
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
}
#endif /* SRC_AST_H_ */
