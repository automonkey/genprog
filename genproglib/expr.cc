#include "expr.h"

namespace genproglib
{

Expr::Expr()
{
}

Expr::~Expr()
{
}

class LiteralExpr : public Expr
{
public:
    explicit LiteralExpr( EXPR_VAL );

    EXPR_VAL Evaluate() const;

protected:
    ~LiteralExpr()
    {
    }

private:
    EXPR_VAL mVal;
};

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

void Expr::DestroyExpr( Expr* expr )
{
    delete expr;
}

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : mVal( val )
{
}

EXPR_VAL LiteralExpr::Evaluate() const
{
    return mVal;
}

}

