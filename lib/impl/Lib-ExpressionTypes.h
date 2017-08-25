#ifndef LIB_EXPRESSIONTYPES
#define LIB_EXPRESSIONTYPES

#include <string>
#include "Lib-Expression.h"

namespace Lib {

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

class Input : public Expr
{
public:
    EXPR_VAL EvaluateForInput( EXPR_VAL ) const;

protected:
    ~Input() {}

private:
    std::string name;
};

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

/// created expr takes ownership of provided subexpressions
Expr* CreateInput();

/// created expr takes ownership of provided subexpressions
Expr* CreateLiteralExpr( EXPR_VAL );

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
/*created expr takes ownership of provided subexpressions*/     \
Expr* Create##EXPR_NAME( Expr* op1, Expr* op2 );


DEFINE_BINARY_OPERATOR_EXPR( AdditionExpr )
DEFINE_BINARY_OPERATOR_EXPR( SubtractionExpr )
DEFINE_BINARY_OPERATOR_EXPR( MultiplicationExpr )
DEFINE_BINARY_OPERATOR_EXPR( DivisionExpr )

}

#endif
