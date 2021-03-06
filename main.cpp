#include <Tokenizer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <iostream>
#include <exception>
#include <Exceptions.h>
#include <memory>
#include <queue>

#ifdef WITH_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

using namespace std;
using namespace JarJar;

auto output = queue<string>();

string getInput();
void print();

int main(int argc, char *argv[])
{
   Interpreter *i = new Interpreter(&output);

   while (true) {
      try
      {
         string input = getInput();

         if(input == "quit") break;

         Tokenizer t = Tokenizer(input);
         Parser p = Parser(t.getTokens());

         i->interpert(p.eval());
         print();



      }
      catch (const runtime_error &e)
      {
         cout << "Caught runtime error " << type(e) << endl;
         cout << e.what() << endl;
      }
   }

   delete i;
}

void print()
{
   while(!output.empty())
   {
      cout << output.front() << endl;
      output.pop();
   }
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
