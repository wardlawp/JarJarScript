#include<Environment.h>

namespace JarJar {

   Environment::Environment(Environment * parent)
   {
      this->parent = parent;
      m = map<string, SObject>();
   }

   void Environment::assign(string name, Object* value)
   {
      if(m.count(name) != 1){
         if(parent == 0) {
             throw VariableNotDefinedException(name + " was not declared");
         }
         return parent->assign(name, value);
      }

      define(name, value);
   }

   void Environment::define(string name, Object* value)
   {
      if(value == 0 || value == Null::addr()){
         m[name] = Null::get();
      } else {
         m[name] = SObject(Object::copyObject(value));
      }
   }

   SObject Environment::get(string name)
   {
      if(m.count(name) != 1){
         if(parent != 0)
         {
            return parent->get(name);
         }

         throw VariableNotDefinedException(name + " was not declared");
      }

      return m[name];
   }

}
