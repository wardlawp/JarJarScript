#include <Interpreter.h>

namespace JarJar
{

   void Interpreter::interpert(vector<shared_ptr<Statement>> statements)
   {
      for(auto statement: statements)
      {
         try {
            visitStatement(statement.get());
         } catch (InterpreterException &e){
            //todo
            cout << e.what() << endl;
         }

      }
   }

   SafeObject Interpreter::visitBinary(Binary * expr)
   {
      SafeObject lRef = visitExpression(expr->left);
      SafeObject rRef = visitExpression(expr->right);

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

      return SafeObject(val);
   }

   SafeObject Interpreter::visitUnary(Unary * expr)
   {
      SafeObject ref = visitExpression(expr->right);
      Object * right = ref.get();


      switch (expr->op.type) {
         case TokenType::SUB:
           return SafeObject(right->negate());
         case TokenType::NOT:
             return SafeObject(right->operator !());
        default:
           throw InterpreterException("Unary operation " + getStringRepr(expr->op.type) + " not implemented");
      }

   }

   SafeObject Interpreter::visitAssign(Assign * expr)
   {
      SafeObject value = visitExpression(expr->exp);

      env->assign(expr->name.value, value);

      return value;
   }

   SafeObject Interpreter::visitLogical(Logical * expr)
   {
      SafeObject leftResult = visitExpression(expr->left);

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

   SafeObject Interpreter::visitCall(Call * expr)
   {
      //Eval callee
      SafeObject so = visitExpression(expr->callee);

      Function* fun = dynamic_cast<Function*>(so.get());
      if (fun == nullptr)
      {
         throw InterpreterException("Object not callable"); //TODO improve
         //TODO throw exception
      }

      if (expr->arguments.size() != fun->arity())
      {
         //TODO throw exception
      }

      vector<SafeObject> args{};

      for (auto e : expr->arguments)
      {
         args.push_back(visitExpression(e));
      }


      return fun->call(this, args);
   }

   SafeObject Interpreter::visitGrouping(Grouping * expr)
   {
      return visitExpression(expr->exp);
   }

   SafeObject Interpreter::visitLiteral(Literal * expr)
   {
      return SafeObject(expr->value);
   }

   SafeObject Interpreter::visitVariable(Variable * expr)
   {
      return env->get(expr->name.value);
   }

   void Interpreter::visitPrintStatment(PrintStatment * statement)
   {
      SafeObject result = visitExpression(statement->expr);

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
         env->define(name, 0);
      }
   }

   void Interpreter::visitBlock(Block * statement){
     
      return executeBlock(statement, new Environment(env));
   }

   void Interpreter::executeBlock(Block * statement, Environment* targetEnv)
   {
      Environment* previous = env;
      env = targetEnv;

      for(auto s: statement->statements)
      {
         visitStatement(s);
      }

      delete env;
      env = previous;
   }

   void Interpreter::visitIfStatement(IfStatement * statement)
   {
      SafeObject truth = visitExpression(statement->truthTest);
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
      Object* funObj = new Function(decl);
      env->define(decl->name.value, SafeObject(funObj));
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

   SafeObject Interpreter::getVar(string name)
   {
      return env->get(name);
   }

}
