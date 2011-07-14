#include "TestFramework.h"
#include "expr.h"

#include <iostream>
#include <memory>

namespace
{

class ExprPtr
{
public:
    ExprPtr( genproglib::Expr* ptr )
        : mPtr( ptr )
    {
    }

    ~ExprPtr()
    {
        genproglib::Expr::DestroyExpr( mPtr );
    }

    genproglib::Expr* operator->() const
    {
        return mPtr;
    }

    genproglib::Expr* Ptr() const
    {
        return mPtr;
    }

private:
    genproglib::Expr* mPtr;
};

void LiteralExpr()
{
    ExprPtr le( genproglib::Expr::CreateLiteralExpr( 42 ) );

    IG_ASSERT( le->Evaluate() == 42 );
}

void AdditionExpr()
{
    ExprPtr firstOperand( genproglib::Expr::CreateLiteralExpr( 21 ) );
    ExprPtr secondOperand( genproglib::Expr::CreateLiteralExpr( 27 ) );

    ExprPtr expr( genproglib::Expr::CreateAdditionExpr(
        firstOperand.Ptr(),
        secondOperand.Ptr() ) );

    IG_ASSERT( expr->Evaluate() == 48 );
}

void SubtractionExpr()
{
    ExprPtr op1( genproglib::Expr::CreateLiteralExpr( 78 ) );
    ExprPtr op2( genproglib::Expr::CreateLiteralExpr( 32 ) );

    ExprPtr expr( genproglib::Expr::CreateSubtractionExpr(
        op1.Ptr(),
        op2.Ptr() ) );

    IG_ASSERT( expr->Evaluate() == 46 );
}

void MultiplicationExpr()
{
    ExprPtr op1( genproglib::Expr::CreateLiteralExpr( 12 ) );
    ExprPtr op2( genproglib::Expr::CreateLiteralExpr( 6 ) );

    ExprPtr expr( genproglib::Expr::CreateMultiplicationExpr(
        op1.Ptr(),
        op2.Ptr() ) );

    IG_ASSERT( expr->Evaluate() == 72 );
}

void DivisionExpr()
{
    ExprPtr op1( genproglib::Expr::CreateLiteralExpr( 81 ) );
    ExprPtr op2( genproglib::Expr::CreateLiteralExpr( 9 ) );

    ExprPtr expr( genproglib::Expr::CreateDivisionExpr(
        op1.Ptr(),
        op2.Ptr() ) );

    IG_ASSERT( expr->Evaluate() == 9 );
}

}

IG_BEGIN_TESTS
IG_TEST_ENTRY( LiteralExpr )
IG_TEST_ENTRY( AdditionExpr )
IG_TEST_ENTRY( SubtractionExpr )
IG_TEST_ENTRY( MultiplicationExpr )
IG_TEST_ENTRY( DivisionExpr )
IG_END_TESTS

IG_TEST_MAIN

