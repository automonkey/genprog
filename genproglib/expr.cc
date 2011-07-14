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

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : mVal( val )
{
}

EXPR_VAL LiteralExpr::Evaluate() const
{
    return mVal;
}

#define DEFINE_BINARY_OPERATOR_EXPR( EXPR_NAME )    \
class EXPR_NAME : public Expr                       \
{                                                   \
public:                                             \
    EXPR_NAME( Expr* op1, Expr* op2 )               \
        : mOp1( op1 )                               \
        , mOp2( op2 )                               \
    {                                               \
    }                                               \
                                                    \
    EXPR_VAL Evaluate() const;                      \
                                                    \
private:                                            \
    Expr* mOp1;                                     \
    Expr* mOp2;                                     \
};

DEFINE_BINARY_OPERATOR_EXPR( AdditionExpr ) 
EXPR_VAL AdditionExpr::Evaluate() const
{
    return mOp1->Evaluate() + mOp2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( SubtractionExpr ) 
EXPR_VAL SubtractionExpr::Evaluate() const
{
    return mOp1->Evaluate() - mOp2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( MultiplicationExpr ) 
EXPR_VAL MultiplicationExpr::Evaluate() const
{
    return mOp1->Evaluate() * mOp2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( DivisionExpr ) 
EXPR_VAL DivisionExpr::Evaluate() const
{
    return mOp1->Evaluate() / mOp2->Evaluate();
}

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

Expr* Expr::CreateAdditionExpr( Expr* op1, Expr* op2 )
{
    return new AdditionExpr( op1, op2 );
}

Expr* Expr::CreateSubtractionExpr( Expr* op1, Expr* op2 )
{
    return new SubtractionExpr( op1, op2 );
}

Expr* Expr::CreateMultiplicationExpr( Expr* op1, Expr* op2 )
{
    return new MultiplicationExpr( op1, op2 );
}

Expr* Expr::CreateDivisionExpr( Expr* op1, Expr* op2 )
{
    return new DivisionExpr( op1, op2 );
}

void Expr::DestroyExpr( Expr* expr )
{
    delete expr;
}

}

