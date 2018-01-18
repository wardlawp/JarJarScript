#ifndef SRC_FUNCTION_H_
#define SRC_FUNCTION_H_

#include <Environment.h>
#include <Typedefs.h>
#include <vector>
#include <Object.h>
#include <Statement.h>
#include <Interpreter.h>
#include <Return.h>
#include <string>

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


   typedef std::shared_ptr<JarJar::Environment> RefEnvironment;

   class Function : public Callable, public Object
   {
      RefEnvironment closure;
   public:
      Function(FunctionDeclaration* fun, RefEnvironment _closure) : decl(fun), closure(_closure) {};

      ~Function() override
      {
         delete decl;
      }

      virtual bool assignByRef() const override
      {
         return true;
      }

      virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);
     

      virtual int arity()
      {
         return decl->parameters.size();
      }

      virtual string toStr() const
      {
         return "<Function> " + decl->name.value;
      }

      virtual Object* clone()
      {
         //TODO  -throw
         return this;
      }


      virtual bool truthy() {
         //TODO: this would be a programmer bug: if(functionName) ...
         //Therefore throw an Exception
         return false;
      }

      FunctionDeclaration* decl;
   };
}


#endif