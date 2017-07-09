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

         ~PrintStatment()
         {
            delete expr;
         }

         Expression * expr;

   };

   class ExpressionStatment: public Statement
   {
      public:
         ExpressionStatment(Expression * e)
         {
            expr = e;
         };

         ~ExpressionStatment()
         {
            delete expr;
         }

         Expression * expr;

   };

   class VariableStatment: public Statement
   {
      public:
         VariableStatment(Token n, Expression * e) : name(n)
         {
            expr = e;
         };

         ~VariableStatment()
         {
            delete expr;
         }

         Token name;
         Expression * expr;

   };

   class Block: public Statement
   {
      public:
         Block(vector<Statement*> s) : statements(s) { };

         ~Block()
         {
            for(auto s: statements) delete s;
         }

         vector<Statement*> statements;
   };

   class IfStatement: public Statement
   {
      public:
         IfStatement(Expression* exp, Statement* trueBranch, Statement* falseBranch = nullptr)
         {
            truthTest = exp;
            this->trueBranch = trueBranch;
            this->falseBranch = falseBranch;
         };

         ~IfStatement()
         {
            delete truthTest;
            delete trueBranch;
            delete falseBranch;
         }

         Expression* truthTest;
         Statement* trueBranch;
         Statement* falseBranch;
   };


}
#endif /* SRC_STATMENT_H_ */
