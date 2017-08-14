#include <Function.h>

namespace JarJar {
   SafeObject Function::call(Interpreter* interpreter, vector<SafeObject> args) 
   {
      Environment* funEnv = new Environment(interpreter->global);

      for (int i = 0; i < arity(); i++)
      {
         funEnv->define(decl->parameters[i].value, args[i]);
      }

      interpreter->executeBlock(decl->body, funEnv);

      //TODO
      return Null::get();
   }
}