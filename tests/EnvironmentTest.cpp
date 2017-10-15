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
      SObject value = SObject(new Int(4));
      global.define("test", value.get());

      SObject storedValue = global.get("test");

      //Pointers won't equal, but values should
      CHECK(storedValue.get() != value.get());
      Bool* b = dynamic_cast<Bool*>(storedValue->operator==(value.get()));
      CHECK(b->val == true);
      delete b;
   }

   SECTION("Define without initialized")
   {
      global.define("test", nullptr);

      SObject storedValue = global.get("test");

      CHECK(storedValue.get() == Null::addr());
   }

   SECTION("Assign writes over")
   {
      SObject value = SObject(new Int(4));
      global.define("test", value.get());

      Bool* b = dynamic_cast<Bool*>(global.get("test")->operator==(value.get()));
      CHECK(b->val == true);
      delete b;

      global.assign("test", Null::addr());

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
      SObject value = SObject(new Int(4));
      global.define("test", value.get());

      Environment inner = Environment(&global);

      Bool* b = dynamic_cast<Bool*>(inner.get("test")->operator==(value.get()));
      CHECK(b->val == true);
      delete b;
   }

   SECTION("Modify parent variables")
   {
      SObject value = SObject(new Int(4));
      global.define("test", value.get());

      Environment inner = Environment(&global);

      Bool* b = dynamic_cast<Bool*>(global.get("test")->operator==(value.get()));
      CHECK(b->val == true);
      delete b;

      inner.assign("test", Null::addr());

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


