#include "Lib-ExpressionGenerator.h"
#include "Lib-ExpressionTypes.h"

#include <random>
#include <string>

namespace Lib {

class RandomOperatorGeneratorImpl : public RandomOperatorGenerator {

public:
    mutable std::random_device rd;
    mutable std::mt19937 gen;
    mutable std::uniform_int_distribution<> rng;

    RandomOperatorGeneratorImpl()
        : gen(rd())
        , rng(0, 3) {
    }

    virtual Operator Next() const {
        return static_cast<Operator>(rng(gen));
    }
};

std::shared_ptr< RandomOperatorGenerator > CreateRandomOperatorGenerator() {
    return std::shared_ptr< RandomOperatorGenerator >( new RandomOperatorGeneratorImpl );
}

class RandomLiteralGeneratorImpl : public RandomLiteralGenerator {

public:
    mutable std::random_device rd;
    mutable std::mt19937 gen;
    mutable std::uniform_int_distribution<> rng;

    RandomLiteralGeneratorImpl()
        : gen(rd())
        , rng(0, 10) {
    }

    virtual EXPR_VAL Next() const {
        return rng(gen);
    }
};

std::shared_ptr< RandomLiteralGenerator > CreateRandomLiteralGenerator() {
    return std::shared_ptr< RandomLiteralGenerator >( new RandomLiteralGeneratorImpl );
}

ExpressionGenerator::ExpressionGenerator(std::shared_ptr< RandomOperatorGenerator > opGen, std::shared_ptr<RandomLiteralGenerator> litGen)
    : randomOperatorGenerator(opGen)
    , randomLiteralGenerator(litGen) {
}

ExprPtr ExpressionGenerator::Generate() {

    Expr* lhs = Lib::CreateInput();
    Expr* rhs = Lib::CreateLiteralExpr(randomLiteralGenerator->Next());

    RandomOperatorGenerator::Operator op = randomOperatorGenerator->Next();
    if(op == RandomOperatorGenerator::Operator::Addition) {
        return Lib::ExprPtr(Lib::CreateAdditionExpr(lhs, rhs));
    } else if(op == RandomOperatorGenerator::Operator::Subtraction) {
        return Lib::ExprPtr(Lib::CreateSubtractionExpr(lhs, rhs));
    } else if(op == RandomOperatorGenerator::Operator::Multiplication) {
        return Lib::ExprPtr(Lib::CreateMultiplicationExpr(lhs, rhs));
    } else {
        return Lib::ExprPtr(Lib::CreateDivisionExpr(lhs, rhs));
    }
}

}
