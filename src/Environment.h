#ifndef SRC_ENVIRONMENT_H_
#define SRC_ENVIRONMENT_H_

#include <map>
#include <string>
#include <Object.h>
#include <Exceptions.h>
#include <Typedefs.h>
#include <typeinfo>

using namespace std;

namespace JarJar {

   class Environment {
      public:
         Environment(Environment * parent = 0);
         void define(string name, Object* value);
         void assign(string name, Object* value);
         SObject get(string name);

      private:
         Environment * parent;
         map<string, SObject> m;
   };
}



#endif /* SRC_ENVIRONMENT_H_ */
