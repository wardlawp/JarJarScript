#include <catch.hpp>
#include <Environment.h>
#include <Object.h>
#include <Exceptions.h>

using namespace std;
using namespace JarJar;


TEST_CASE( "Test Un-Nested", "Un-Nested" )
{
   Environment global = Environment();

   SECTION("Define with initialized")
   {
      Object * value = new Int(4);
      global.define("test", value);

      Object * storedValue = global.get("test");

      CHECK(storedValue == value);
   }

   SECTION("Define without initialized")
   {
      global.define("test", 0);

      Object * storedValue = global.get("test");

      CHECK(storedValue == Null::get());
   }

   SECTION("Assign writes over")
   {
      Object * value = new Int(4);
      global.define("test", value);

      CHECK(global.get("test") == value);

      global.assign("test", Null::get());

      CHECK(global.get("test") == Null::get());

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
      Object * value = new Int(4);
      global.define("test", value);

      Environment inner = Environment(&global);

      CHECK(inner.get("test") == value);
   }

   SECTION("Modify parent variables")
   {
      Object * value = new Int(4);
      global.define("test", value);

      Environment inner = Environment(&global);

      CHECK(global.get("test") == value);

      inner.assign("test", Null::get());

      CHECK(inner.get("test") == Null::get());
      CHECK(global.get("test") == Null::get());
   }

   SECTION("Defined variables are owned by inner scope")
   {
      Environment inner = Environment(&global);
      inner.define("test", 0);

      REQUIRE_THROWS_AS(global.get("test"), VariableNotDefinedException);
      CHECK(inner.get("test") == Null::get());
   }
}


