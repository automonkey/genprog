#include "catch.hpp"

#include "Lib-Expression.h"

#include <iostream>
#include <sstream>
#include <string>

TEST_CASE( "Literal expression should evaluate to value created with", "[operations]" ) {

    Lib::Expr* le = Lib::Expr::CreateLiteralExpr(42);
    REQUIRE(le->Evaluate() == 42);
}

