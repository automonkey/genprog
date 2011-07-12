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

class AdditionExpr : public Expr
{
public:
    AdditionExpr( Expr*, Expr* );

    EXPR_VAL Evaluate() const;

private:
    Expr* mOp1;
    Expr* mOp2;
};

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

Expr* Expr::CreateAdditionExpr( Expr* op1, Expr* op2 )
{
    return new AdditionExpr( op1, op2 );
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

AdditionExpr::AdditionExpr( Expr* op1, Expr* op2 )
    : mOp1( op1 )
    , mOp2( op2 )
{
}

EXPR_VAL AdditionExpr::Evaluate() const
{
    return mOp1->Evaluate() + mOp2->Evaluate();
}

}

