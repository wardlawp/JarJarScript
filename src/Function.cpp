#pragma once
#include <Function.h>
#include <Typedefs.h>

using namespace std;

namespace JarJar {
   SObject Function::call(Interpreter* interpreter, const vector<SObject> &args) 
   {
      RefEnvironment funEnv = make_shared<Environment>(closure.get());

      for (int i = 0; i < arity(); i++)
      {
         funEnv->define(decl->parameters[i].value, args[i]);
      }

      try {
         interpreter->executeBlock(decl->body.get(), funEnv);
      } catch (Return ret) {
         return ret.result;
      }
      
      return Null::get();
   }
}