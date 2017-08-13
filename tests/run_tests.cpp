// Main entry point for tests
#define CATCH_IMPL  
#include <catch.hpp>

int main(int argc, char * argv[]) {
   int result = Catch::Session().run(argc, argv);
   std::cout << "Press enter to continue...";
   std::cin.get();
   return (result < 0xff ? result : 0xff);
}