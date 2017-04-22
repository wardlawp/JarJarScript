#include <Tokenizer.h>
#include <Visitors.h>
#include <Parser.h>
#include <iostream>
#include <AST.h>

using namespace std;
using namespace JarJar;

int main(int argc, char *argv[]) {
   ASTPrinter * printer = new ASTPrinter();

   while(true){

      cout << ">";
      string input;
      cin >> input;

      Tokenizer t = Tokenizer(input);
      Parser p = Parser(t.getTokens());

      cout << printer->visit(p.eval()) << endl;
   }

}
