#ifndef  __EMSCRIPTEN__
   #error Emscripten is required
#endif 

// Modify the following two definitions to target page elements
// Input should be a textarea
// Output should be a div
#define INPUT_ID "input"
#define OUTPUT_ID "output"

#include <emscripten.h>
#include <emscripten/html5.h>

#include <Tokenizer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <Exceptions.h>

#include <algorithm>
#include <sstream>
#include <queue>


using namespace std;
using namespace JarJar;

const int FPS = 20;
char buff[4096];
auto output = queue<string>();
string latestInput;
Interpreter* i;

// Forward Declarations
bool processInput();
void print();
void log(string);
void loopIteration();
void replaceEndls(string&);

int main(int argc, char *argv[])
{
   log("Starting...");
   
   output.push("Welcome to JarJarScript! Type <b>print \"Hello world\";</b> to begin.");
   print();

   i = new Interpreter(&output);

   emscripten_set_main_loop(loopIteration, FPS, 1);
   
   delete i;
   return 0;
}

void loopIteration()
{
      try
      {
         if (!processInput())
         {
            return;
         }
        
         log("Running Statement");
         output.push(latestInput);

         Tokenizer t = Tokenizer(latestInput);
         Parser p = Parser(t.getTokens());

         i->interpert(p.eval());
        
      }
      catch (const runtime_error &e)
      {
         stringstream msgStream;
         msgStream << "Caught runtime error " << type(e) << endl << e.what();
         string msg = msgStream.str();
         log(msg);
         output.push(msg);
      }

      print();
}

// Javascript
char c_log[]      = "console.log('%s');";
char getInput[]   = "document.getElementById('" INPUT_ID "').value;";
char wipeInput[]  = "document.getElementById('" INPUT_ID "').value = '';";
char beginOutput[]= "var input = document.getElementById('" INPUT_ID "');";
char scroll[]     = "var el = document.getElementById('" OUTPUT_ID "'); el.scrollTop = el.scrollHeight;";
char c_addLine[]  = "var line = document.createElement('p'); line.innerHTML = '%s'; "  
                    "input.parentNode.insertBefore(line, input);";

void log(string input) 
{
   replaceEndls(input);
   sprintf(buff, c_log, input.c_str());
   emscripten_run_script(buff);
}

void addline(stringstream& builder, string& content)
{
   replaceEndls(content);
   sprintf(buff, c_addLine, content.c_str());
   builder << ' ' << buff << ' ';
}

void print()
{
   if (output.size() == 0) {
      return;
   }

   stringstream builder;
   builder << beginOutput;

   while(!output.empty())
   {
      addline(builder, output.front());
      output.pop();
   }

   emscripten_run_script(builder.str().c_str());
   emscripten_run_script(scroll);
}


// returns true if there is input ready to process
bool processInput()
{
   string received = emscripten_run_script_string(getInput);

   auto pos = received.find('\n'); 

   if(pos != std::string::npos) {
      latestInput = received.substr(0,pos);
      emscripten_run_script(wipeInput);
      return true;
   }  

   return false;
}

// For JS encoding purposes
void replaceEndls(string& input)
{
   string::size_type pos = 0; // Must initialize
   while ((pos = input.find("\n", pos)) != string::npos)
   {
      input.replace(pos, 1, "\\n");
   }
}