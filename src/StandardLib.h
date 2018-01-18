#include <Environment.h>
#include <Typedefs.h>
#include <vector>
#include <Object.h>
#include <Statement.h>
#include <Interpreter.h>
#include <string>

using namespace std;



namespace JarJar
{
   namespace StandardLib 
   {

      static const string OpenFileName = "open";
      static const string ReadFileName = "read";
      static const string WriteLineName = "write_line";
      static const string WriteName = "write";
      static const string CloseFileName = "close";

      class StandardLibFuncion : public Callable, public Object
      {
      public:
         /* StdLib functions are stateless*/
         virtual  Object* clone() override
         {
            return this;
         }

         virtual bool truthy() override
         {
            //todo throw
            return false;
         }

         virtual bool assignByRef() const override
         {
            return true;
         }

         virtual string toStr() const
         {
            return "<Stdlib Function> " + name();
         }

         virtual string name() const = 0;
      };

      class OpenFile : public StandardLibFuncion
      {
      public:
         OpenFile() {};
         ~OpenFile() override {}

         virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);


         virtual int arity() override
         {
            return 2;
         }


         virtual string name() const override
         {
            return OpenFileName;
         }
      };

      class ReadFile : public StandardLibFuncion
      {
      public:
         ReadFile() {}
         ~ReadFile() override {}

         virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);

         virtual int arity() override
         {
            return 1;
         }

         virtual string name() const override
         {
            return ReadFileName;
         }
      };

      class CloseFile : public StandardLibFuncion
      {
      public:
         CloseFile() {}
         ~CloseFile() override {}

         virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);

         virtual int arity() override
         {
            return 1;
         }

         virtual string name() const override
         {
            return CloseFileName;
         }
      };

      class WriteLine : public StandardLibFuncion
      {
      public:
         WriteLine() {}
         ~WriteLine() override {}

         virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);

         virtual int arity() override
         {
            return 2;
         }

         virtual string name() const override
         {
            return WriteLineName;
         }
      };

      class Write : public StandardLibFuncion
      {
      public:
         Write() {}
         ~Write() override {}

         virtual SObject call(Interpreter* interpreter, const vector<SObject> & args);

         virtual int arity() override
         {
            return 2;
         }

         virtual string name() const override
         {
            return WriteName;
         }
      };

   }
}