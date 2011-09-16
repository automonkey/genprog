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
    ExprPtr expr(
        genproglib::Expr::CreateAdditionExpr(
            genproglib::Expr::CreateLiteralExpr( 21 ),
            genproglib::Expr::CreateLiteralExpr( 27 )
        )
    );

    IG_ASSERT( expr->Evaluate() == 48 );
}

void SubtractionExpr()
{
    ExprPtr expr(
        genproglib::Expr::CreateSubtractionExpr(
            genproglib::Expr::CreateLiteralExpr( 78 ),
            genproglib::Expr::CreateLiteralExpr( 32 )
        )
    );

    IG_ASSERT( expr->Evaluate() == 46 );
}

void MultiplicationExpr()
{
    ExprPtr expr(
        genproglib::Expr::CreateMultiplicationExpr(
            genproglib::Expr::CreateLiteralExpr( 12 ),
            genproglib::Expr::CreateLiteralExpr( 6 )
        )
    );

    IG_ASSERT( expr->Evaluate() == 72 );
}

void DivisionExpr()
{
    ExprPtr expr(
        genproglib::Expr::CreateDivisionExpr(
            genproglib::Expr::CreateLiteralExpr( 81 ),
            genproglib::Expr::CreateLiteralExpr( 9 )
        )
    );

    IG_ASSERT( expr->Evaluate() == 9 );
}

void MultiOperatorExpr()
{
    // (4 * 3) + ((9 / 3) + 5) = 20
    ExprPtr expr(
        genproglib::Expr::CreateAdditionExpr(
            genproglib::Expr::CreateMultiplicationExpr(
                genproglib::Expr::CreateLiteralExpr( 4 ),
                genproglib::Expr::CreateLiteralExpr( 3 )
            ),
            genproglib::Expr::CreateAdditionExpr(
                genproglib::Expr::CreateDivisionExpr(
                    genproglib::Expr::CreateLiteralExpr( 9 ),
                    genproglib::Expr::CreateLiteralExpr( 3 )
                ),
                genproglib::Expr::CreateLiteralExpr( 5 )
            )
        )
    );

    IG_ASSERT( expr->Evaluate() == 20 );
}

}

IG_BEGIN_TESTS
IG_TEST_ENTRY( LiteralExpr )
IG_TEST_ENTRY( AdditionExpr )
IG_TEST_ENTRY( SubtractionExpr )
IG_TEST_ENTRY( MultiplicationExpr )
IG_TEST_ENTRY( DivisionExpr )
IG_TEST_ENTRY( MultiOperatorExpr )
IG_END_TESTS

IG_TEST_MAIN

