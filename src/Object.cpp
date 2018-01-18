#include<Object.h>

using namespace JarJar;

auto dontDeleteMe = [](Object*) {};
shared_ptr<JarJar::Object> JarJar::Null::instance = shared_ptr<JarJar::Object>(new Null(), dontDeleteMe);