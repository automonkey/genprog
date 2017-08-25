#ifndef LIB_EXPRESSIONGENERATOR
#define LIB_EXPRESSIONGENERATOR

#include "Lib-Expression.h"

#include <memory>

namespace Lib
{

class RandomOperatorGenerator {

public:
    enum Operator {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    virtual Operator Next() const = 0;
};

std::shared_ptr< RandomOperatorGenerator > CreateRandomOperatorGenerator();

class RandomLiteralGenerator {

public:
    virtual EXPR_VAL Next() const = 0;
};

std::shared_ptr< RandomLiteralGenerator > CreateRandomLiteralGenerator();

class ExpressionGenerator {

private:
    std::shared_ptr< RandomOperatorGenerator > randomOperatorGenerator;
    std::shared_ptr< RandomLiteralGenerator > randomLiteralGenerator;

public:
    ExpressionGenerator(std::shared_ptr<RandomOperatorGenerator>, std::shared_ptr<RandomLiteralGenerator>);

    Lib::ExprPtr Generate();
};

}

#endif
