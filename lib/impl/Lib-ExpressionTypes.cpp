#include "Lib-ExpressionTypes.h"

#include <sstream>

namespace Lib
{

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

EXPR_VAL LiteralExpr::EvaluateForInput( EXPR_VAL ) const
{
    return val;
}

Expr* CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

EXPR_VAL Input::EvaluateForInput( EXPR_VAL input ) const
{
    return input;
}

Expr* CreateInput()
{
    return new Input();
}

#define DEFINE_BINARY_OPERATOR_CREATOR( EXPR_NAME )             \
Expr* Create##EXPR_NAME( Expr* op1, Expr* op2 ) {               \
    return new EXPR_NAME(op1, op2);                             \
}

DEFINE_BINARY_OPERATOR_CREATOR( AdditionExpr )
DEFINE_BINARY_OPERATOR_CREATOR( SubtractionExpr )
DEFINE_BINARY_OPERATOR_CREATOR( MultiplicationExpr )
DEFINE_BINARY_OPERATOR_CREATOR( DivisionExpr )

EXPR_VAL AdditionExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) + op2->EvaluateForInput(input);
}

EXPR_VAL SubtractionExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) - op2->EvaluateForInput(input);
}

EXPR_VAL MultiplicationExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) * op2->EvaluateForInput(input);
}

EXPR_VAL DivisionExpr::EvaluateForInput( EXPR_VAL input ) const
{
    return op1->EvaluateForInput(input) / op2->EvaluateForInput(input);
}

}

