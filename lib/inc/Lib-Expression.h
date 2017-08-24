#ifndef LIB_APPUSAGESTRINGGENERATION
#define LIB_APPUSAGESTRINGGENERATION

#include <map>
#include <memory>

namespace Lib
{

typedef int EXPR_VAL;

class Expr
{
public:
    virtual EXPR_VAL EvaluateForInput( EXPR_VAL ) const = 0;

    static Expr* CreateLiteralExpr( EXPR_VAL );

    /// created expr takes ownership of provided subexpressions
    static Expr* CreateAdditionExpr( Expr*, Expr* );

    /// created expr takes ownership of provided subexpressions
    static Expr* CreateInput();

    /// created expr takes ownership of provided subexpressions
    static Expr* CreateSubtractionExpr( Expr*, Expr* );

    /// created expr takes ownership of provided subexpressions
    static Expr* CreateMultiplicationExpr( Expr*, Expr* );

    /// created expr takes ownership of provided subexpressions
    static Expr* CreateDivisionExpr( Expr*, Expr* );

    virtual ~Expr();

protected:
    Expr();
};

typedef std::shared_ptr< Lib::Expr > ExprPtr;

}

#endif
