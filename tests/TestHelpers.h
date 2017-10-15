#ifndef TESTS_TESTHELPERS_H_
#define TESTS_TESTHELPERS_H_

#include <AST.h>
#include <memory>
#include <Statement.h>
#include <catch.hpp>
#include <Token.h>
#include <Parser.h>
#include <Tokenizer.h>

using namespace JarJar;

Expression *                    getFirstExpression(const vector<shared_ptr<Statement>>&  statement);
vector<shared_ptr<Statement>>   parse(const vector<Token>& tokens);
vector<Token>                   stringToTokens(const string& input);


#endif /* TESTS_TESTHELPERS_H_ */
