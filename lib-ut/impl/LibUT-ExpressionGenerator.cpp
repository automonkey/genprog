#include "catch.hpp"

#include <queue>

#include "Lib-Expression.h"
#include "Lib-ExpressionTypes.h"
#include "Lib-ExpressionGenerator.h"

#include "LibUT-TestMatchers.h"

class FakeRandomOperatorGenerator : public Lib::RandomOperatorGenerator {
public:
    mutable std::queue<Operator> operatorsToReturn;

    virtual Operator Next() const {
        if(operatorsToReturn.empty()) {
            throw std::runtime_error("Requested more operators than loaded with");
        }

        auto next = operatorsToReturn.front();
        operatorsToReturn.pop();
        return next;
    }
};

class FakeRandomLiteralGenerator : public Lib::RandomLiteralGenerator {
public:
    mutable std::queue<Lib::EXPR_VAL> valuesToReturn;

    virtual Lib::EXPR_VAL Next() const {
        if(valuesToReturn.empty()) {
            throw std::runtime_error("Requested more literals than loaded with");
        }

        auto next = valuesToReturn.front();
        valuesToReturn.pop();
        return next;
    }
};

TEST_CASE( "Should generate expression with random operator", "[exp-gen]" ) {

    std::shared_ptr< FakeRandomOperatorGenerator > fakeRandomOpGen( new FakeRandomOperatorGenerator );
    std::shared_ptr< Lib::RandomLiteralGenerator > randomLitGen( Lib::CreateRandomLiteralGenerator() );
    Lib::ExpressionGenerator exprGen(fakeRandomOpGen, randomLitGen);

    {
        fakeRandomOpGen->operatorsToReturn.push(Lib::RandomOperatorGenerator::Operator::Addition);
        Lib::ExprPtr expr = exprGen.Generate();
        CHECK_THAT(expr, IsAdditionOperator());
    }

    {
        fakeRandomOpGen->operatorsToReturn.push(Lib::RandomOperatorGenerator::Operator::Subtraction);
        Lib::ExprPtr expr = exprGen.Generate();
        CHECK_THAT(expr, IsSubtractionOperator());
    }

    {
        fakeRandomOpGen->operatorsToReturn.push(Lib::RandomOperatorGenerator::Operator::Multiplication);
        Lib::ExprPtr expr = exprGen.Generate();
        CHECK_THAT(expr, IsMultiplicationOperator());
    }

    {
        fakeRandomOpGen->operatorsToReturn.push(Lib::RandomOperatorGenerator::Operator::Division);
        Lib::ExprPtr expr = exprGen.Generate();
        CHECK_THAT(expr, IsDivisionOperator());
    }
}

TEST_CASE( "Should generate expression with random literal", "[exp-gen]" ) {

    std::shared_ptr< Lib::RandomOperatorGenerator > randomOpGen( Lib::CreateRandomOperatorGenerator() );
    std::shared_ptr< FakeRandomLiteralGenerator > fakeRandomLiteralGen( new FakeRandomLiteralGenerator );
    Lib::ExpressionGenerator exprGen(randomOpGen, fakeRandomLiteralGen);

    Lib::EXPR_VAL someValue = 4;
    {
        Lib::EXPR_VAL SEVEN = 7;

        fakeRandomLiteralGen->valuesToReturn.push(SEVEN);
        Lib::ExprPtr expr = exprGen.Generate();

        auto generatedExpr = dynamic_cast< Lib::BinaryExpr* >(expr.get());
        CHECK_THAT(generatedExpr->op2, IsLiteral());
        auto generatedLiteral = generatedExpr->op2;
        REQUIRE(generatedLiteral->EvaluateForInput(someValue) == SEVEN);
    }

    {
        Lib::EXPR_VAL THREE = 3;

        fakeRandomLiteralGen->valuesToReturn.push(THREE);
        Lib::ExprPtr expr = exprGen.Generate();

        auto generatedExpr = dynamic_cast< Lib::BinaryExpr* >(expr.get());
        CHECK_THAT(generatedExpr->op2, IsLiteral());
        auto generatedLiteral = generatedExpr->op2;
        REQUIRE(generatedLiteral->EvaluateForInput(someValue) == THREE);
    }
}

TEST_CASE( "Should generate expression including input", "[exp-gen]" ) {

    std::shared_ptr< Lib::RandomOperatorGenerator > randomOpGen( Lib::CreateRandomOperatorGenerator() );
    std::shared_ptr< Lib::RandomLiteralGenerator > randomLitGen( Lib::CreateRandomLiteralGenerator() );

    Lib::ExpressionGenerator exprGen(randomOpGen, randomLitGen);

    Lib::ExprPtr expr = exprGen.Generate();

    auto generatedExpr = dynamic_cast< Lib::BinaryExpr* >(expr.get());
    CHECK_THAT(generatedExpr->op1, IsInput());
}
