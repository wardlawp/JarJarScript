#include <catch.hpp>
#include <Environment.h>
#include <Object.h>
#include <Exceptions.h>
#include <Typedefs.h>

using namespace std;
using namespace JarJar;


TEST_CASE( "Test Un-Nested", "Un-Nested" )
{
   Environment global = Environment();

   SECTION("Define with initialized")
   {
      SafeObject value = SafeObject(new Int(4));
      global.define("test", value);

      SafeObject storedValue = global.get("test");

      //Pointers won't equal, but values should
      CHECK(storedValue.get() != value.get());
      Bool* b = dynamic_cast<Bool*>(storedValue->operator==(value.get()));
      CHECK(b->val == true);
      delete b;
   }

   SECTION("Define without initialized")
   {
      global.define("test", 0);

      SafeObject storedValue = global.get("test");

      CHECK(storedValue.get() == Null::addr());
   }

   SECTION("Assign writes over")
   {
      SafeObject value = SafeObject(new Int(4));
      global.define("test", value);

      Bool* b = dynamic_cast<Bool*>(global.get("test")->operator==(value.get()));
      CHECK(b->val == true);
      delete b;

      global.assign("test", Null::get());

      CHECK(global.get("test").get()  == Null::addr());

   }

   SECTION("Assign to not defined throws exception")
   {
      REQUIRE_THROWS_AS(global.assign("test", 0), VariableNotDefinedException);
   }
}

TEST_CASE( "Test Nested", "Assign" )
{
   Environment global = Environment();

   SECTION("Access parent variables")
   {
      SafeObject value = SafeObject(new Int(4));
      global.define("test", value);

      Environment inner = Environment(&global);

      Bool* b = dynamic_cast<Bool*>(inner.get("test")->operator==(value.get()));
      CHECK(b->val == true);
      delete b;
   }

   SECTION("Modify parent variables")
   {
      SafeObject value = SafeObject(new Int(4));
      global.define("test", value);

      Environment inner = Environment(&global);

      Bool* b = dynamic_cast<Bool*>(global.get("test")->operator==(value.get()));
      CHECK(b->val == true);
      delete b;

      inner.assign("test", Null::get());

      CHECK(inner.get("test").get() == Null::addr());
      CHECK(global.get("test").get() == Null::addr());
   }

   SECTION("Defined variables are owned by inner scope")
   {
      Environment inner = Environment(&global);
      inner.define("test", 0);

      REQUIRE_THROWS_AS(global.get("test"), VariableNotDefinedException);
      CHECK(inner.get("test").get() == Null::addr());
   }
}


