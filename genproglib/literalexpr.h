#ifndef GENPROGLIB_LITERALEXPR
#define GENPROGLIB_LITERALEXPR

namespace genproglib
{

typedef int EXPR_VAL;

class LiteralExpr
{
public:
    LiteralExpr( EXPR_VAL );

    EXPR_VAL Evaluate() const;

private:
    EXPR_VAL mVal;
};

}

#endif

