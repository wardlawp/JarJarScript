#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <string>
#include <Exceptions.h>
#include <typeinfo>
using namespace std;

namespace JarJar
{
   class Object
   {
      public:
         virtual ~Object() {}
         virtual string toStr() = 0;

         virtual Object * negate()
         {
            throw ObjectMethodDoesNotExistException(notImplementedMsg(__PRETTY_FUNCTION__));
         }

         virtual Object * operator+(Object *  other)
         {
            throw ObjectMethodDoesNotExistException(notImplementedMsg(__PRETTY_FUNCTION__));
         }

         virtual Object * operator-(Object *  other)
         {
            throw ObjectMethodDoesNotExistException(notImplementedMsg(__PRETTY_FUNCTION__));
         }

         virtual Object * operator*(Object *  other)
         {
            throw ObjectMethodDoesNotExistException(notImplementedMsg(__PRETTY_FUNCTION__));
         }

         virtual Object * operator/(Object *  other)
         {
            throw ObjectMethodDoesNotExistException(notImplementedMsg(__PRETTY_FUNCTION__));
         }

         virtual Object * operator=(Object *  other)
         {
            throw ObjectMethodDoesNotExistException(notImplementedMsg(__PRETTY_FUNCTION__));
         }

      private:
         string notImplementedMsg(string name)
         {
            string msg =  " does not implement method ";
            msg = typeid(this).name() + msg;
            return msg+ name;
         }

   };

   class Int: public Object
   {
      public:
         int val;


         Int(int _val) {
            val = _val;
         }

         virtual string toStr(){
            return to_string(val);
         }

         virtual Object * negate()
         {
            return new Int(-val);
         }

         virtual Object * operator+(Object * other)
         {
            return new Int(val + cast(other)->val);
         }

         virtual Object * operator-(Object * other)
         {
            return new Int(val - cast(other)->val);
         }

         virtual Object * operator*(Object * other)
         {
            return new Int(val * cast(other)->val);
         }

         virtual Object * operator/(Object * other)
         {
            return new Int(val / cast(other)->val);
         }

         virtual Object * operator=(Object * other)
         {
            val = cast(other)->val;
            return this;
         }

      private:
         Int * cast(Object * other)
         {
            return dynamic_cast<Int*>(other);
         }
   };
}

#endif /* SRC_OBJECT_H_ */
