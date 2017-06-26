#include <Tokenizer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <iostream>
#include <exception>
#include <Exceptions.h>

#ifdef WITH_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

using namespace std;
using namespace JarJar;

vector<string> output = vector<string>();

string getInput();
void print();

int main(int argc, char *argv[])
{
   Interpreter *i = new Interpreter(&output);

   while (true) {
      try
      {
         Tokenizer t = Tokenizer(getInput());
         Parser p = Parser(t.getTokens());
         vector<Statement*> statements = p.eval();
         i->interpert(statements);
         print();

         for(auto s: statements) delete s;

      }
      catch (const runtime_error &e)
      {
         cout << "Caught runtime error " << type(e) << endl;
         cout << e.what() << endl;
      }
   }
}

void print()
{
   for(string s: output)
   {
      cout << s << endl;
   }

   output.clear();
}

string getInput()
{
#ifdef WITH_READLINE
   char * line = readline(">");
   add_history(line);
   string input = line;
   free(line);
   return input;
#else
   cout << ">";
   string input;
   getline(cin, input);
   return input;
#endif
}
