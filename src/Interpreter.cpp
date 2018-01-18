#include <Interpreter.h>
#include <StandardLib.h>

#define ADD_STD_FUNC(NAME, CLASS)env->define(NAME, SObject(new CLASS));
namespace JarJar
{

   Interpreter::Interpreter(queue<string> * op)
   {
      output = op;
      global = make_shared<Environment>();
      env = global;

      initStdLibFunctions();
   };

   void Interpreter::initStdLibFunctions()
   {
      ADD_STD_FUNC(StandardLib::OpenFileName, StandardLib::OpenFile);
      ADD_STD_FUNC(StandardLib::ReadFileName, StandardLib::ReadFile);
      ADD_STD_FUNC(StandardLib::CloseFileName, StandardLib::CloseFile);
      ADD_STD_FUNC(StandardLib::WriteLineName, StandardLib::WriteLine);
      ADD_STD_FUNC(StandardLib::WriteName, StandardLib::Write);
   }

   void Interpreter::interpert(vector<shared_ptr<Statement>> statements)
   {
      for(auto statement: statements)
      {
         try {
            visitStatement(statement.get());
         } catch (InterpreterException &e){
            cout << e.what() << endl;
         }
      }
   }

   SObject Interpreter::visitBinary(Binary * expr)
   {
      SObject lRef = visitExpression(expr->left);
      SObject rRef = visitExpression(expr->right);

      Object * left = lRef.get();
      Object * right = rRef.get();

      typeCheck(left,right, expr->op);

      Object* val;

      switch (expr->op.type) {
         case TokenType::ADD :
            val = left->operator+(right);
            break;
         case TokenType::SUB :
            val = left->operator-(right);
            break;
         case TokenType::MUL :
            val = left->operator*(right);
            break;
         case TokenType::DIV :
            val = left->operator/(right);
            break;
         case TokenType::ASSIGN :
            val = left->operator=(right);
            break;
         case TokenType::GT :
            val = left->operator>(right);
            break;
        case TokenType::GTE :
           val = left->operator>=(right);
           break;
        case TokenType::LT :
           val = left->operator<(right);
           break;
        case TokenType::LTE :
           val = left->operator<=(right);
           break;
        case TokenType::EQUALS :
           val = left->operator==(right);
           break;
         default:
            throw InterpreterException("Binary operation " + getStringRepr(expr->op.type) + " not implemented");
      }

      return SObject(val);
   }

   SObject Interpreter::visitUnary(Unary * expr)
   {
      SObject ref = visitExpression(expr->right);
      Object * right = ref.get();


      switch (expr->op.type) {
         case TokenType::SUB:
           return SObject(right->negate());
         case TokenType::NOT:
             return SObject(right->operator !());
        default:
           throw InterpreterException("Unary operation " + getStringRepr(expr->op.type) + " not implemented");
      }

   }

   SObject Interpreter::visitAssign(Assign * expr)
   {
      SObject value = visitExpression(expr->exp);

      env->assign(expr->name.value, value);

      return value;
   }

   SObject Interpreter::visitLogical(Logical * expr)
   {
      SObject leftResult = visitExpression(expr->left);

      if(expr->t == TokenType::OR)
      {
         if(leftResult->truthy()){
               return leftResult;
         }
      } else {
         if(!leftResult->truthy()){
            return leftResult;
         }
      }

      return visitExpression(expr->right);
   }

   SObject Interpreter::visitCall(Call * expr)
   {
      //Eval callee
      //Our function "c" is getting deleted here
      SObject so = visitExpression(expr->callee);
      //so.

      Callable* fun = dynamic_cast<Callable*>(so.get());
      if (fun == nullptr)
      {
         throw InterpreterException(so->toStr() + " not callable");
      }

      if (expr->arguments.size() != fun->arity())
      {
         throw InterpreterException("Invalid number of arguments supplied");
      }

      vector<SObject> args{};

      for (auto e : expr->arguments)
      {
         args.push_back(visitExpression(e));
      }


      return fun->call(this, args);
   }

   SObject Interpreter::visitGrouping(Grouping * expr)
   {
      return visitExpression(expr->exp);
   }

   SObject Interpreter::visitLiteral(Literal * expr)
   {
      return SObject(expr->value);
   }

   SObject Interpreter::visitVariable(Variable * expr)
   {
      return env->get(expr->name.value);
   }

   void Interpreter::visitPrintStatment(PrintStatment * statement)
   {
      SObject result = visitExpression(statement->expr);

      if(output != nullptr){
         output->push(result->toStr());
      }
   }

   void Interpreter::visitExpressionStatment(ExpressionStatment * statement)
   {
      visitExpression(statement->expr);
   }

   void Interpreter::visitVariableStatment(VariableStatment * statement)
   {
      string name = statement->name.value;
      if(statement->expr != 0)
      {
         env->define(name, visitExpression(statement->expr));
      } else {
         env->define(name, Null::get());
      }
   }

   void Interpreter::visitBlock(Block * statement){
     
      return executeBlock(statement, make_shared<Environment>(env.get()));
   }

   void Interpreter::executeBlock(Block * statement, RefEnvironment targetEnv)
   {
      RefEnvironment previous = env;
      env = targetEnv;
      
      auto returnEnvToPrevious = [this, &previous]() 
      { 
         this->env = previous;
      };

      try
      {
         for (auto s : statement->statements)
         {
            visitStatement(s);
         }
      } catch (Return ret) {
         returnEnvToPrevious(); //here
         throw ret;
      }

      returnEnvToPrevious();
   }

   void Interpreter::visitIfStatement(IfStatement * statement)
   {
      SObject truth = visitExpression(statement->truthTest);
      Object * t = truth.get();

      if(t->truthy())
      {
         visitStatement(statement->trueBranch);
      } else if (statement->falseBranch != nullptr){
         visitStatement(statement->falseBranch);
      }
   }

   void Interpreter::visitWhileStatement(WhileStatement* statement)
   {
      while(visitExpression(statement->truthTest)->truthy())
      {
         visitStatement(statement->body);
      }
   }

   
   void Interpreter::visitFunctionDeclaration(FunctionDeclaration* decl)
   {
      SObject funObj = SObject(new Function(new FunctionDeclaration(*decl), env));
      env->define(decl->name.value, funObj); 
   }

   void Interpreter::visitReturnStatement(ReturnSatatment* statement)
   {
      SObject obj;
      if (statement->exp != nullptr) {
         obj = visitExpression(statement->exp);
      }  else {
         obj = Null::get();
      }

      throw Return(obj);
   }

   void Interpreter::typeCheck(Object * left, Object * right, Token t)
   {
      if(typeid(*left) != typeid(*right)){
         string leftStr = type(*left);
         string rightStr = type(*right);
         string msg = "Left (" + leftStr + ") and right (" + rightStr + ") operand types do not match";
         throw TypeMissMatchException(t, msg);
      }
   }

   SObject Interpreter::getVar(string name)
   {
      return env->get(name);
   }

}
