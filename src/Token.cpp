#include "Token.h"
#include <iostream>

using namespace JarJar;
using namespace std;

namespace JarJar {
    Token::Token(TokenType t, string tx, string v, int l)
    {
        type = t;
        text = tx;
        value = v;
        line = l;
    }
}
