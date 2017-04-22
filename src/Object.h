#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <string>
#include <iostream>
using namespace std;

namespace JarJar
{
   class Object
   {
      public:
         virtual ~Object() {}
         virtual string toStr() = 0;
   };

   class Int: public Object
   {
      private:
         int val;
      public:


         Int(int _val) {
            val = _val;
         }

         virtual string toStr(){
            return to_string(val);
         }

         Int operator+(Int other)
         {
            return Int(val + other.val);
         }

         Int operator-(Int other)
         {
            return Int(val - other.val);
         }

         Int operator*(Int other)
         {
            return Int(val * other.val);
         }

         Int operator/(Int other)
         {
            return Int(val / other.val);
         }

         Int operator=(Int other)
         {
            val = other.val;
            return *this;
         }
   };
}

#endif /* SRC_OBJECT_H_ */
