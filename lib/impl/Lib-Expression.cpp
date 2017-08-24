#include "Lib-Expression.h"

#include <string>
#include <sstream>

namespace Lib
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

    EXPR_VAL EvaluateForInput( EXPR_VAL ) const;

protected:
    ~LiteralExpr() {}

private:
    EXPR_VAL val;
};

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : val( val )
{
}

EXPR_VAL LiteralExpr::EvaluateForInput( EXPR_VAL ) const
{
    return val;
}

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

class Input : public Expr
{
public:
    EXPR_VAL EvaluateForInput( EXPR_VAL ) const;

protected:
    ~Input() {}

private:
    std::string name;
};

EXPR_VAL Input::EvaluateForInput( EXPR_VAL input ) const
{
    return input;
}

Expr* Expr::CreateInput()
{
    return new Input();
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
    EXPR_VAL EvaluateForInput( EXPR_VAL ) const;                \
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
EXPR_VAL AdditionExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) + op2->EvaluateForInput(input);
}

DEFINE_BINARY_OPERATOR_EXPR( SubtractionExpr )
EXPR_VAL SubtractionExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) - op2->EvaluateForInput(input);
}

DEFINE_BINARY_OPERATOR_EXPR( MultiplicationExpr )
EXPR_VAL MultiplicationExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) * op2->EvaluateForInput(input);
}

DEFINE_BINARY_OPERATOR_EXPR( DivisionExpr )
EXPR_VAL DivisionExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) / op2->EvaluateForInput(input);
}

}

