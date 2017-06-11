#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <string>
#include <Exceptions.h>
#include <Type.h>
#include <TokenConstants.h>
using namespace std;

namespace JarJar
{
   class Object
   {
      public:
         virtual ~Object()
         {
         }
         virtual string toStr() const = 0;

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

         static Bool * TRUE()
         {
            static Bool TRUE = Bool(true);
            return & TRUE;
         }

         static Bool * FALSE()
         {
            static Bool FALSE = Bool(false);
            return & FALSE;
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

   class Null : public Object
   {
      public:
         static Null * get()
         {
            static Null instance;
            return & instance;
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
   };


}

#endif /* SRC_OBJECT_H_ */
