#ifndef SRC_STATMENT_H_
#define SRC_STATMENT_H_

#include <TokenConstants.h>
#include <AST.h>
#include <Object.h>
#include <Token.h>
#include <vector>


namespace JarJar
{
   class Statement
   {
      public:
         virtual ~Statement() {}
   };

   class PrintStatment: public Statement
   {
      public:
         PrintStatment(Expression * e)
         {
            expr = e;
         };

         Expression * expr;

   };

   class ExpressionStatment: public Statement
   {
      public:
         ExpressionStatment(Expression * e)
         {
            expr = e;
         };

         Expression * expr;

   };

   class VariableStatment: public Statement
   {
      public:
         VariableStatment(Token n, Expression * e) : name(n)
         {
            expr = e;
         };

         Token name;
         Expression * expr;

   };

   class Block: public Statement
   {
      public:
         Block(vector<Statement*> s) : statements(s) { };
         vector<Statement*> statements;
   };


}
#endif /* SRC_STATMENT_H_ */
