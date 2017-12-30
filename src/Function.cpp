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
         funEnv->define(decl->parameters[i].value, args[i].get());
      }

      try {
         interpreter->executeBlock(decl->body.get(), funEnv);
      } catch (Return ret) {
         return ret.result;
      }
      
      return Null::get();
   }

   const string OpenFile::name = "open";

   static void checkOpenFileArgs(const vector<SObject> &args)
   {
      if (args.size() != 2) {
         throw StdLibException(OpenFile::name + " takes two string arguments");
      }

      auto isJJString = [](Object* o) {
         return (dynamic_cast<String*>(o) != nullptr);
      };

      if (!isJJString(args[0].get()) || !isJJString(args[1].get())) {

         throw StdLibException(OpenFile::name +  " takes two string arguments");
      }

      string mode = args[1]->toStr();

      if (mode != "r" && mode != "w")
      {

         throw StdLibException(OpenFile::name + "'s second argument must be 'r' or 'w'");
      }
   }

   SObject OpenFile::call(Interpreter* interpreter, const vector<SObject> &args)
   {
      checkOpenFileArgs(args);
      return SObject(new File(args[0]->toStr(), args[1]->toStr()));
   }
}