#include <Tokenizer.h>
#include <Visitors.h>
#include <Parser.h>
#include <iostream>
#include <AST.h>
#include <Interpreter.h>

using namespace std;
using namespace JarJar;

int main(int argc, char *argv[]) {
   ASTPrinter * printer = new ASTPrinter();

   while(true){

      cout << ">";
      string input;
      getline(cin, input);

      Tokenizer t = Tokenizer(input);
      vector<Token> tokens = t.getTokens();
      Parser p = Parser(tokens);
      Expression * e = p.eval();

      Interpreter *i = new Interpreter();
      Object * obj = i->visit(e);

      cout << obj->toStr() << endl;
   }

}
