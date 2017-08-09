#include "catch.hpp"

#include "Lib-Expression.h"

#include <iostream>
#include <sstream>
#include <string>

TEST_CASE( "Literal expression should evaluate to value created with", "[operations]" ) {

    Lib::ExprPtr le(Lib::Expr::CreateLiteralExpr(42));
    REQUIRE(le->Evaluate() == 42);
}

TEST_CASE( "Addition expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr threePlusTwo(Lib::Expr::CreateAdditionExpr(
        Lib::Expr::CreateLiteralExpr(3),
        Lib::Expr::CreateLiteralExpr(2)));
    REQUIRE(threePlusTwo->Evaluate() == 5);
}

TEST_CASE( "Subtraction expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr threeMinusTwo( Lib::Expr::CreateSubtractionExpr(
        Lib::Expr::CreateLiteralExpr(3),
        Lib::Expr::CreateLiteralExpr(2)));
    REQUIRE(threeMinusTwo->Evaluate() == 1);
}

TEST_CASE( "Multiplication expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr threeMinusTwo(Lib::Expr::CreateMultiplicationExpr(
        Lib::Expr::CreateLiteralExpr(3),
        Lib::Expr::CreateLiteralExpr(2)));
    REQUIRE(threeMinusTwo->Evaluate() == 6);
}

TEST_CASE( "Division expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr EightDividedByTwo(Lib::Expr::CreateDivisionExpr(
        Lib::Expr::CreateLiteralExpr(8),
        Lib::Expr::CreateLiteralExpr(2)));
    REQUIRE(EightDividedByTwo->Evaluate() == 4);
}

TEST_CASE( "Should evaluate multi-operator expression", "[operations]" ) {

    Lib::ExprPtr multiOperatorExpr(
        Lib::Expr::CreateAdditionExpr(
            Lib::Expr::CreateMultiplicationExpr(
                Lib::Expr::CreateLiteralExpr(4),
                Lib::Expr::CreateLiteralExpr(3)),
            Lib::Expr::CreateAdditionExpr(
                Lib::Expr::CreateDivisionExpr(
                    Lib::Expr::CreateLiteralExpr(9),
                    Lib::Expr::CreateLiteralExpr(3)),
                Lib::Expr::CreateLiteralExpr(5))));

    REQUIRE(multiOperatorExpr->Evaluate() == ((4 * 3) + ((9 / 3) + 5)));
}
