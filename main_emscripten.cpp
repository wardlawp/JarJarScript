#ifndef  __EMSCRIPTEN__
   #error Emscripten is required
#endif // ! __EMSCRIPTEN__


#include <emscripten.h>
#include <emscripten/html5.h>
#include <Tokenizer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <Exceptions.h>

#include <sstream>
#include <exception>
#include <queue>


using namespace std;
using namespace JarJar;

auto output = queue<string>();


// Forward Declarations
bool processInput();
void print();
void log(string);
void oneIter();
string latestInput;

Interpreter* i;

int main(int argc, char *argv[])
{
   log("Starting...");

   i = new Interpreter(&output);

   emscripten_set_main_loop(oneIter, 5, 1);
   
   delete i;
   return 0;
}

void oneIter()
{
      try
      {
         if (!processInput())
         {
            return;
         }
        
         log("Running Statement");
         

         Tokenizer t = Tokenizer(latestInput);
         Parser p = Parser(t.getTokens());

         i->interpert(p.eval());
         print();	

      }
      catch (const runtime_error &e)
      {
         stringstream msgStream;
         msgStream << "Caught runtime error " << type(e);

         string line1, line2;
         line1 = msgStream.str();
         line2 = e.what();

         log(line1);
         log(line2);
         output.push(line1);
         output.push(line2);
      }
}

void log(string input) {
   string cmd = "console.log('" +  input  + "');";
   emscripten_run_script(cmd.c_str());
}

char setOutput[] = 
"var ul = document.getElementById(\"output\"); var li;";

void print()
{
   if (output.size() == 0) {
      return;
   }

   stringstream builder;
   builder << setOutput;
   while(!output.empty())
   {
      builder << "li = document.createElement(\"li\"); \
                  li.appendChild(document.createTextNode(\"" 
              << output.front() << "\")); \
                  ul.appendChild(li);";

      output.pop();
   }
   emscripten_run_script(builder.str().c_str());
}

char getInputJS[] = "document.getElementById(\'input\').value;";
char wipeInput[] = "document.getElementById(\'input\').value = '';";
int counter = 0;

bool processInput()
{
   string received = emscripten_run_script_string(getInputJS);
   if(received.back() == '\n') { 
      latestInput = received.substr(counter,received.size() -1);
      emscripten_run_script(wipeInput);
      return true;
   }  

   return false;
}
