#include "Lib-Expression.h"

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

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : val( val )
{
}

EXPR_VAL LiteralExpr::Evaluate() const
{
    return val;
}

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

class BinaryExpr : public Expr
{
public:
    BinaryExpr( Expr* op1, Expr* op2 )
        : op1( op1 )
        , op2( op2 )
    {
    }

    ExprPtr op1;
    ExprPtr op2;

protected:
    ~BinaryExpr()
    {
    }
};

#define DEFINE_BINARY_OPERATOR_EXPR( EXPR_NAME )                \
class EXPR_NAME : public BinaryExpr                             \
{                                                               \
public:                                                         \
    EXPR_NAME( Expr* op1, Expr* op2 )                           \
        : BinaryExpr( op1, op2 )                                \
    {                                                           \
    }                                                           \
                                                                \
    EXPR_VAL Evaluate() const;                                  \
                                                                \
protected:                                                      \
    ~EXPR_NAME()                                                \
    {                                                           \
    }                                                           \
};                                                              \
                                                                \
Expr* Expr::Create##EXPR_NAME( Expr* op1, Expr* op2 ) {         \
    return new EXPR_NAME(op1, op2);                             \
}


DEFINE_BINARY_OPERATOR_EXPR( AdditionExpr )
EXPR_VAL AdditionExpr::Evaluate() const
{
    return op1->Evaluate() + op2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( SubtractionExpr )
EXPR_VAL SubtractionExpr::Evaluate() const
{
    return op1->Evaluate() - op2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( MultiplicationExpr )
EXPR_VAL MultiplicationExpr::Evaluate() const
{
    return op1->Evaluate() * op2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( DivisionExpr )
EXPR_VAL DivisionExpr::Evaluate() const
{
    return op1->Evaluate() / op2->Evaluate();
}

}

