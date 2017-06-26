#ifndef SRC_ENVIRONMENT_H_
#define SRC_ENVIRONMENT_H_

#include <map>
#include <string>
#include <Object.h>
#include <Exceptions.h>

using namespace std;

namespace JarJar {

   class Environment {
      public:
         Environment(Environment * parent = 0);

         ~Environment()
         {
            for(auto val: m)
               Object::deleteObject(val.second);
         }


         void define(string name, Object* value);
         void assign(string name, Object* value);
         Object * get(string name);

      private:
         Environment * parent;
         map<string, Object*> m;
   };
}



#endif /* SRC_ENVIRONMENT_H_ */
