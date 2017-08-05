#include "Lib-Expression.h"

#include <iostream>

namespace Lib
{

class LiteralExpr : public Expr
{
public:
    explicit LiteralExpr( EXPR_VAL );

    EXPR_VAL Evaluate() const;

protected:
    ~LiteralExpr() {}

private:
    EXPR_VAL val;
};

Expr::Expr()
{
}

Expr::~Expr()
{
}

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : val( val )
{
}

EXPR_VAL LiteralExpr::Evaluate() const
{
    return val;
}

}

