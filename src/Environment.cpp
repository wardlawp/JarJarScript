#include<Environment.h>

namespace JarJar {

   Environment::Environment(Environment * parent)
   {
      this->parent = parent;
      m = map<string, SafeObject>();
   }

   void Environment::assign(string name, SafeObject value)
   {
      if(m.count(name) != 1){
         if(parent == 0) {
             throw VariableNotDefinedException(name + " was not declared");
         }
         return parent->assign(name, value);
      }

      m[name] = SafeObject(Object::copyObject(value.get()));
   }

   void Environment::define(string name, SafeObject value)
   {
      if(value == 0){
         m[name] = Null::get();
      } else {
         m[name] = SafeObject(Object::copyObject(value.get()));
      }


   }

   SafeObject Environment::get(string name)
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
