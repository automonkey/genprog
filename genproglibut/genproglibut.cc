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

}

IG_BEGIN_TESTS
IG_TEST_ENTRY( LiteralExpr )
IG_TEST_ENTRY( AdditionExpr )
IG_END_TESTS

IG_TEST_MAIN

