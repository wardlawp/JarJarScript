#include <catch.hpp>
#include <Tokenizer.h>

using namespace JarJar;

TEST_CASE( "Tokenizer foo returns bar", "foo" ) {
    REQUIRE( Tokenizer::foo() == "bar" );
}
