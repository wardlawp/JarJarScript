#pragma once
#include <StandardLib.h>
#include <Typedefs.h>

using namespace std;

namespace JarJar 
{
   namespace StandardLib
   {
      static auto isJJString = [](Object* o) {
         return (dynamic_cast<String*>(o) != nullptr);
      };

      static void checkOpenFileArgs(const vector<SObject> &args)
      {
         if (args.size() != 2) {
            throw StdLibException(OpenFileName + " takes two string arguments");
         }

         if (!isJJString(args[0].get()) || !isJJString(args[1].get())) {

            throw StdLibException(OpenFileName + " takes two string arguments");
         }

         string mode = args[1]->toStr();

         if (mode != "r" && mode != "w")
         {
            throw StdLibException(OpenFileName + "'s second argument must be 'r' or 'w'");
         }
      }

      SObject OpenFile::call(Interpreter* interpreter, const vector<SObject> &args)
      {
         checkOpenFileArgs(args);
         return SObject(new File(args[0]->toStr(), args[1]->toStr()));
      }

      static void checkFileArgs(string name, const vector<SObject> &args)
      {
         if (args.size() != 1) {
            throw StdLibException(name + " takes one file arguments");
         }

         if (dynamic_cast<File*>(args[0].get()) == nullptr){
            throw StdLibException(name + " takes a file argument");
         }
      }

      SObject ReadFile::call(Interpreter* interpreter, const vector<SObject> &args)
      {
         checkFileArgs(ReadFileName,args);
         File* file = dynamic_cast<File*>(args[0].get());
         return file->read();
      }

      SObject CloseFile::call(Interpreter* interpreter, const vector<SObject> &args)
      {
         checkFileArgs(CloseFileName, args);
         File* file = dynamic_cast<File*>(args[0].get());
         file->close();

         return Null::get();
      }

      static void checkWriteArgs(string name, const vector<SObject> &args)
      {
         if (args.size() != 2) {
            throw StdLibException(name + " takes one file arguments");
         }

         if (dynamic_cast<File*>(args[0].get()) == nullptr) {
            throw StdLibException(name + " takes a file argument (argument 0)");
         }

         if (!isJJString(args[1].get())) {
            throw StdLibException(OpenFileName + " takes a string arguments (argument 1)");
         }
      }

      SObject Write::call(Interpreter* interpreter, const vector<SObject> &args)
      {
         checkWriteArgs(CloseFileName, args);

         File* file = dynamic_cast<File*>(args[0].get());
         String* str = dynamic_cast<String*>(args[1].get());

         file->write(str->val);

         return Null::get();
      }

      SObject WriteLine::call(Interpreter* interpreter, const vector<SObject> &args)
      {
         checkWriteArgs(CloseFileName, args);

         File* file = dynamic_cast<File*>(args[0].get());
         String* str = dynamic_cast<String*>(args[1].get());

         file->writeLine(str->val);

         return Null::get();
      }
   }
}