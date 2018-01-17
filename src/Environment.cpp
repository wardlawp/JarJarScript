#include<Environment.h>

namespace JarJar {

   Environment::Environment(Environment * parent)
   {
      this->parent = parent;
      m = map<string, SObject>();
   }

   void Environment::assign(string name, SObject value)
   {
      if(m.count(name) != 1){
         if(parent == nullptr) {
             throw VariableNotDefinedException(name + " was not declared");
         }
         return parent->assign(name, value);
      }

      define(name, value);
   }

   void Environment::define(string name, SObject value)
   {
      if(value.get() == Null::addr()){
         m[name] = Null::get();
      } else if (value->assignByRef()) {
         m[name] = value;
      } else {
         m[name] = SObject(value->clone());
      }
   }

   SObject Environment::get(string name)
   {
      if(m.count(name) != 1){
         if(parent != nullptr)
         {
            return parent->get(name);
         }

         throw VariableNotDefinedException(name + " was not declared");
      }

      return SObject(m[name]);
   }

}
