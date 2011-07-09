#include "TestFramework.h"
#include "literalexpr.h"

#include <iostream>

namespace
{

void LiteralExpr()
{
    genproglib::LiteralExpr le( 42 );

    IG_ASSERT( le.Evaluate() == 42 );
}

}

IG_BEGIN_TESTS
IG_TEST_ENTRY( LiteralExpr )
IG_END_TESTS

IG_TEST_MAIN

