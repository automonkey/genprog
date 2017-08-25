#include "catch.hpp"

#include "Lib-Expression.h"
#include "Lib-ExpressionTypes.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

TEST_CASE( "Literal expression should evaluate to value created with", "[operations]" ) {

    Lib::ExprPtr le(Lib::CreateLiteralExpr(42));
    REQUIRE(le->EvaluateForInput(0) == 42);
}

TEST_CASE( "Variable should evaluate to value passed in to evaluate", "[operations]" ) {

    Lib::ExprPtr var(Lib::CreateInput());

    REQUIRE(var->EvaluateForInput(42) == 42);
}

TEST_CASE( "Binary expressions should evaluate children with variable values", "[operations]" ) {

    Lib::ExprPtr varPlusZero(Lib::CreateAdditionExpr(
        Lib::CreateLiteralExpr(0),
        Lib::CreateInput()));

    REQUIRE(varPlusZero->EvaluateForInput(42) == 42);
}

TEST_CASE( "Addition expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr threePlusTwo(Lib::CreateAdditionExpr(
        Lib::CreateLiteralExpr(3),
        Lib::CreateLiteralExpr(2)));
    REQUIRE(threePlusTwo->EvaluateForInput(0) == 5);
}

TEST_CASE( "Subtraction expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr threeMinusTwo( Lib::CreateSubtractionExpr(
        Lib::CreateLiteralExpr(3),
        Lib::CreateLiteralExpr(2)));
    REQUIRE(threeMinusTwo->EvaluateForInput(0) == 1);
}

TEST_CASE( "Multiplication expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr threeMinusTwo(Lib::CreateMultiplicationExpr(
        Lib::CreateLiteralExpr(3),
        Lib::CreateLiteralExpr(2)));
    REQUIRE(threeMinusTwo->EvaluateForInput(0) == 6);
}

TEST_CASE( "Division expression should evaluate to correct total", "[operations]" ) {

    Lib::ExprPtr EightDividedByTwo(Lib::CreateDivisionExpr(
        Lib::CreateLiteralExpr(8),
        Lib::CreateLiteralExpr(2)));
    REQUIRE(EightDividedByTwo->EvaluateForInput(0) == 4);
}

TEST_CASE( "Should evaluate multi-operator expression", "[operations]" ) {

    Lib::ExprPtr multiOperatorExpr(
        Lib::CreateAdditionExpr(
            Lib::CreateMultiplicationExpr(
                Lib::CreateLiteralExpr(4),
                Lib::CreateLiteralExpr(3)),
            Lib::CreateAdditionExpr(
                Lib::CreateDivisionExpr(
                    Lib::CreateLiteralExpr(9),
                    Lib::CreateLiteralExpr(3)),
                Lib::CreateLiteralExpr(5))));

    REQUIRE(multiOperatorExpr->EvaluateForInput(0) == ((4 * 3) + ((9 / 3) + 5)));
}
