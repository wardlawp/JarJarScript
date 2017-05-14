#include <Tokenizer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <iostream>
#include <exception>
#include <Exceptions.h>
#include <typeinfo>

using namespace std;
using namespace JarJar;

string getInput();

int main(int argc, char *argv[])
{
   Interpreter *i = new Interpreter();

   while (true) {
      try
      {
         Tokenizer t = Tokenizer(getInput());
         Parser p = Parser(t.getTokens());
         Expression * e = p.eval();

         Object * obj = i->visit(e);

         cout << obj->toStr() << endl;
      }
      catch (const runtime_error &e)
      {
         cout << "Caught runtime error " << typeid(e).name() << endl;
         cout << e.what() << endl;
      }
   }
}

string getInput()
{
   cout << ">";
   string input;
   getline(cin, input);
   return input;
}
