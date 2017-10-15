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

      env->assign(expr->name.value, value.get());

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
      SObject so = visitExpression(expr->callee);

      Function* fun = dynamic_cast<Function*>(so.get());
      if (fun == nullptr)
      {
         throw InterpreterException("Object not callable"); //TODO improve
         //TODO throw exception
      }

      if (expr->arguments.size() != fun->arity())
      {
         throw InterpreterException("Invalid number of arguments supplied");
         //TODO throw exception
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
         env->define(name, visitExpression(statement->expr).get());
      } else {
         env->define(name, nullptr);
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
      Object* funObj = new Function(new FunctionDeclaration(*decl));
      env->define(decl->name.value, funObj);
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
