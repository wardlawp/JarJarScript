#include<Object.h>

namespace JarJar
{
   Object* Object::copyObject(Object* obj)
   {
      if (obj != Null::addr()) {
         return obj->clone();
      }

      return obj;
   }

   void Object::deleteObject(Object* obj)
   {
      if (obj != Null::addr() and obj != nullptr) {
         delete obj;
      }
   }
}
