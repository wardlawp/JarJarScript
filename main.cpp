#include <Tokenizer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <Exceptions.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <exception>
#include <queue>

#ifdef WITH_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

using namespace std;
using namespace JarJar;

auto output = queue<string>();

// Error Codes
const int OK = 0;
const int INTERPRET_ERROR = 1;
const int FILE_ERROR = 2;
const int USAGE_ERROR = 3;

const string QUIT = "quit";

// Forward Declarations
int interactiveMode(Interpreter *i);
int fileMode(Interpreter *i, char* filePath);
int interpret(string input, Interpreter* i);
string getInput();
void print();

int main(int argc, char *argv[])
{
   Interpreter *i = new Interpreter(&output);

   int returnVal = 0;

   switch (argc) {
   case 1:
      returnVal = interactiveMode(i);
      break;
   case 2:
      returnVal = fileMode(i, argv[1]);
      break;
   default:
      cerr << "Invalid usage. Supply no argument or path to script file.";
      return USAGE_ERROR;
   }

   delete i;
   return returnVal;
}

int fileMode(Interpreter *i, char* cfilePath)
{
   string filePath = cfilePath;
   bool correctEnding = (0 == filePath.compare(filePath.length() - 2, 2, "jj"));

   if (!correctEnding) {
      cerr << "Incorrect file extension, expected \"*.jj\"";
      return FILE_ERROR;
   }

   ifstream scriptFile(filePath);
   if (scriptFile.is_open())
   {
      stringstream buffer;
      buffer << scriptFile.rdbuf();

      int returnVal = interpret(buffer.str(), i);

      scriptFile.close();
      return returnVal;

   } else {
      cerr << "Unable to open file";
      return FILE_ERROR;
   }
}

int interactiveMode(Interpreter *i)
{
   while (true) {
      string input = getInput();
      if (input == QUIT) break;

      interpret(input, i);
   }

   return OK;
}

int interpret(string input, Interpreter* i)
{
   try
   {
      Tokenizer t = Tokenizer(input);
      Parser p = Parser(t.getTokens());
      i->interpert(p.eval());
      print();
   }
   catch (const runtime_error &e)
   {
      cerr << "Caught runtime error " << type(e) << endl;
      cerr << e.what() << endl;
      return 1;
   }

   return OK;
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
