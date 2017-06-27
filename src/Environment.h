#ifndef SRC_ENVIRONMENT_H_
#define SRC_ENVIRONMENT_H_

#include <map>
#include <string>
#include <Object.h>
#include <Exceptions.h>
#include <Typedefs.h>

using namespace std;

namespace JarJar {

   class Environment {
      public:
         Environment(Environment * parent = 0);
         void define(string name, SafeObject value);
         void assign(string name, SafeObject value);
         SafeObject get(string name);

      private:
         Environment * parent;
         map<string, SafeObject> m;
   };
}



#endif /* SRC_ENVIRONMENT_H_ */
