#include "TestFramework.h"
#include "expr.h"

#include <iostream>

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

private:
    genproglib::Expr* mPtr;
};

void LiteralExpr()
{
    ExprPtr le( genproglib::Expr::CreateLiteralExpr( 42 ) );

    IG_ASSERT( le->Evaluate() == 42 );
}

}

IG_BEGIN_TESTS
IG_TEST_ENTRY( LiteralExpr )
IG_END_TESTS

IG_TEST_MAIN

