#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <string>
#include <Exceptions.h>
#include <Type.h>
#include <TokenConstants.h>
#include <memory>

using namespace std;

namespace JarJar
{
   class Null;
   class Object
   {
      public:
         virtual ~Object(){ }
         virtual string toStr() const = 0;
         virtual Object* clone() = 0;

         static void deleteObject(Object* obj);
         static Object* copyObject(Object* obj);

         virtual Object * negate()
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator+(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator-(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator*(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator/(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator=(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         /**
          * Comparisons
          */
         virtual Object * operator!()
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator>(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator<(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator==(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator>=(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }

         virtual Object * operator<=(Object * other)
         {
            throw ObjectMethodDoesNotExistException(
                  notImplementedMsg(__FUNCTION__));
         }



      private:
         string notImplementedMsg(string name)
         {
            string msg = " does not implement method ";
            msg = type(*this) + msg;
            return msg + name + "()";
         }

   };

   class Bool: public Object
   {
      public:
         bool val;

         Bool(bool _val)
         {
            val = _val;
         }

         ~Bool() {}

         Object* clone()
         {
            return new Bool(*this);
         }

         static Bool * TRUE()
         {
            return new Bool(true);
         }

         static Bool * FALSE()
         {
            return new Bool(false);
         }

         virtual string toStr() const
         {
            return boolsToString.at(val);
         }

         virtual Object * operator=(Object * other)
         {
            val = cast(other)->val;
            return this;
         }

         virtual Object * operator==(Object * other)
         {
            if(this->val == cast(other)->val){
               return TRUE();
            }

            return FALSE();
         }

         virtual Object * operator!=(Object * other)
         {
            if(this->val != cast(other)->val){
               return TRUE();
            }

            return FALSE();
         }

         virtual Object * operator!()
         {
            val = !val;
            return this;
         }

      private:
         Bool * cast(Object * other)
         {
            return dynamic_cast<Bool*>(other);
         }

   };

   template <class T>
   class Numerical: public Object
   {
      public:
         T val;

         Numerical(T _val)
         {
            val = _val;
         }

         ~Numerical() {}

         Object* clone()
         {
            return newChild(val);
         }

         virtual  string toStr() const
         {
            return to_string(val);
         }

         virtual Object * negate()
         {
            return newChild(-val);
         }

         virtual Object * operator+(Object * other)
         {
            return newChild(val + cast(other)->val);
         }

         virtual Object * operator-(Object * other)
         {
            return newChild(val - cast(other)->val);
         }

         virtual Object * operator*(Object * other)
         {
            return newChild(val * cast(other)->val);
         }

         virtual Object * operator/(Object * other)
         {
            Numerical * otherN = cast(other);

            if(otherN->val == 0){
               throw DivideByZeroException();
            }

            return newChild(val / otherN->val);
         }

         virtual Object * operator=(Object * other)
         {
            val = cast(other)->val;
            return this;
         }

         /**
          * Comparisons
          */
         virtual Object * operator!()
         {
            if(this->val != 0){
               return Bool::TRUE();
            }

            return Bool::FALSE();
         }

         virtual Object * operator>(Object * other)
         {
            if(this->val > cast(other)->val){
               return Bool::TRUE();
            }

            return Bool::FALSE();
         }

         virtual Object * operator<(Object * other)
         {
            if(this->val < cast(other)->val){
               return Bool::TRUE();
            }

            return Bool::FALSE();
         }

         virtual Object * operator==(Object * other)
         {
            if(this->val == cast(other)->val){
               return Bool::TRUE();
            }

           return Bool::FALSE();
         }

         virtual Object * operator>=(Object * other)
         {
            if(this->val >= cast(other)->val){
               return Bool::TRUE();
            }

           return Bool::FALSE();
         }

         virtual Object * operator<=(Object * other)
         {
            if(this->val <= cast(other)->val){
              return Bool::TRUE();
            }

          return Bool::FALSE();
         }

      private:
         virtual Numerical * cast(Object * other) = 0;
         virtual Numerical * newChild(T val) = 0;
   };


   class Int: public Numerical<int>
   {
      public:
         Int(int _val) : Numerical(_val) {};
         ~Int() {};
      private:
         virtual Numerical * cast(Object * other)
         {
            return dynamic_cast<Int*>(other);
         }
         virtual Numerical * newChild(int val)
         {
            return new Int(val);
         }
   };

   class Decimal: public Numerical<double>
   {
      public:
         Decimal(double _val) : Numerical(_val) {};
         ~Decimal() {};
      private:
         virtual Numerical * cast(Object * other)
         {
            return dynamic_cast<Decimal*>(other);
         }
         virtual Numerical * newChild(double val)
         {
            return new Decimal(val);
         }
   };

   class String: public Object
   {
      public:
         string val;

         String(string _val)
         {
            val = _val;
         }

         ~String() {}

         Object* clone()
         {
            return new String(*this);
         }

         virtual  string toStr() const
         {
            return "\"" + val + "\"";
         }

         virtual Object * operator+(Object * other)
         {
            return new String(val + cast(other)->val);
         }

         virtual Object * operator=(Object * other)
         {
            val = cast(other)->val;
            return this;
         }

         /**
          * Comparisons
          */
         virtual Object * operator!()
         {
            if(this->val != ""){
               return Bool::TRUE();
            }

            return Bool::FALSE();
         }

         virtual Object * operator>(Object * other)
         {
            if(this->val > cast(other)->val){
               return Bool::TRUE();
            }

            return Bool::FALSE();
         }

         virtual Object * operator<(Object * other)
         {
            if(this->val < cast(other)->val){
               return Bool::TRUE();
            }

            return Bool::FALSE();
         }

         virtual Object * operator==(Object * other)
         {
            if(this->val == cast(other)->val){
               return Bool::TRUE();
            }

           return Bool::FALSE();
         }

         virtual Object * operator>=(Object * other)
         {
            if(this->val >= cast(other)->val){
               return Bool::TRUE();
            }

           return Bool::FALSE();
         }

         virtual Object * operator<=(Object * other)
         {
            if(this->val <= cast(other)->val){
              return Bool::TRUE();
            }

          return Bool::FALSE();
         }

      private:
         String * cast(Object * other)
         {
            return dynamic_cast<String*>(other);
         }

   };

   /**
    * Singleton, use get()
    */
   class Null : public Object
   {
      public:
         /* Explicitly delete these to enforce no copies */
         Null(Null const&) = delete;
         void operator=(Null const&) = delete;

         static shared_ptr<JarJar::Object> get()
         {
            static Null instance;

            auto dontDeleteMe = [](Object*){};
            return shared_ptr<JarJar::Object>(&instance, dontDeleteMe);
         }

         static Object* addr()
         {
            return Null::get().get();
         }

         Object* clone()
         {
            return addr();
         }

         virtual string toStr() const {
            return getStringRepr(TokenType::NADA);
         }

         virtual Object * operator==(Object * other)
         {
            return Bool::TRUE();
         }

      private:
         Null() {};
         ~Null() {};
   };


}

#endif /* SRC_OBJECT_H_ */
