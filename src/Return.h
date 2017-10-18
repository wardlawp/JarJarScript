#pragma once
#include <exception>
#include <Typedefs.h>

using namespace std;

namespace JarJar
{
   class Return : public exception {
   public:
      Return(SObject _result) : result(_result) {}
      SObject result;
   };

}