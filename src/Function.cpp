#include <Function.h>

namespace JarJar {
   SObject Function::call(Interpreter* interpreter, vector<SObject> args) 
   {
      Environment* funEnv = new Environment(interpreter->global);

      for (int i = 0; i < arity(); i++)
      {
         funEnv->define(decl->parameters[i].value, args[i].get());
      }

      interpreter->executeBlock(decl->body.get(), funEnv);

      //TODO
      return Null::get();
   }
}