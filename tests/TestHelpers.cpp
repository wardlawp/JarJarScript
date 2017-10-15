#include <TestHelpers.h>

Expression * getFirstExpression(const vector<shared_ptr<Statement>>&  statements)
{
   auto ptr = statements.front().get();
   REQUIRE(typeid(*ptr) == typeid(ExpressionStatment));
   return dynamic_cast<ExpressionStatment*>(ptr)->expr;
}

vector<shared_ptr<Statement>> parse(const vector<Token>& tokens)
{
   return  Parser(tokens).eval();
}

vector<Token> stringToTokens(const string& input)
{
   return Tokenizer(input).getTokens();
}
