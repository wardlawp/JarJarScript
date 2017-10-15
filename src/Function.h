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
      virtual SObject call(Interpreter* interpreter, const vector<SObject> & args) = 0;
      virtual int arity() = 0;
   };

   class Function : public Callable, public Object
   {
   public:
      Function(FunctionDeclaration* fun) : decl(fun) {};

      ~Function()
      {
         delete decl;
      }

      virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);
     

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
         //TODO: this would be a programmer bug: if(functionName) ...
         //Therefore throw an Exception
         return true;
      }

      FunctionDeclaration* decl;

   };

}


#endif