#ifndef LIB_APPUSAGESTRINGGENERATION
#define LIB_APPUSAGESTRINGGENERATION

#include <iosfwd>

namespace Lib
{

typedef int EXPR_VAL;

class Expr
{
public:
    virtual EXPR_VAL Evaluate() const = 0;

    static Expr* CreateLiteralExpr( EXPR_VAL );

protected:
    Expr();
    virtual ~Expr();
};

}

#endif
