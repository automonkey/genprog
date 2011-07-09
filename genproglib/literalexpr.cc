#include "literalexpr.h"

namespace genproglib
{

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : mVal( val )
{
}

EXPR_VAL LiteralExpr::Evaluate() const
{
    return mVal;
}

}

