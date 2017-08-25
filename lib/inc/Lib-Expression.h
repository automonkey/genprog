#ifndef LIB_EXPRESSION
#define LIB_EXPRESSION

#include <map>
#include <memory>

namespace Lib
{

typedef int EXPR_VAL;

class Expr
{
public:
    virtual EXPR_VAL EvaluateForInput( EXPR_VAL ) const = 0;

    virtual ~Expr();

protected:
    Expr();
};

typedef std::shared_ptr< Lib::Expr > ExprPtr;

}

#endif
