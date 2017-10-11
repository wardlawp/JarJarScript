#ifndef SRC_ASTPRINTER_H_
#define SRC_ASTPRINTER_H_

#include <AST.h>
#include <ExperssionVisitor.h>
#include <string>

namespace JarJar {

   class ASTPrinter : public ExperssionVisitor<string> {
      public:
         virtual string visitBinary(Binary * expr);
         virtual string visitUnary(Unary * expr);
         virtual string visitGrouping(Grouping * expr);
         virtual string visitLiteral(Literal * expr);
         virtual string visitVariable(Variable * expr);
         virtual string visitAssign(Assign * expr);
         virtual string visitLogical(Logical * expr);

      private:
         string wrap(Expression * e);
   };
}

#endif /* SRC_ASTPRINTER_H_ */
