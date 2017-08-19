#ifndef SRC_FUNCTION_H_
#define SRC_FUNCTION_H_

#include <Environment.h>
#include <Typedefs.h>
#include <vector>
#include <Object.h>
#include <Statement.h>
#include <Interpreter.h>

using namespace std;



namespace JarJar
{
   /* Forward Declation */
   class Interpreter;
   /**
    * Interface Callable
    */
   class Callable 
   {
   public:
      virtual SObject call(Interpreter* interpreter, vector<SObject> args) = 0;
      virtual int arity() = 0;
   };

   class Function : public Callable, public Object
   {
   public:
      Function(FunctionDeclaration* fun) : decl(fun) {};

      ~Function()
      {
         //todo?
         //delete decl;
      }

      virtual SObject call(Interpreter* interpreter, vector<SObject> args);
     

      virtual int arity()
      {
         return decl->parameters.size();
      }

      virtual string toStr() const
      {
         return "TODO";

      }

      virtual Object* clone()
      {
         //TODO 
         return this;
      }


      virtual bool truthy() {
         //TODO must eval?
         return true;
      }

      FunctionDeclaration* decl;

   };

}


#endif