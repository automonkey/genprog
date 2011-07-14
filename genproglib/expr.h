#ifndef GENPROGLIB_LITERALEXPR
#define GENPROGLIB_LITERALEXPR

namespace genproglib
{

typedef int EXPR_VAL;

class Expr
{
public:
    virtual EXPR_VAL Evaluate() const = 0;

    static Expr* CreateLiteralExpr( EXPR_VAL );
    static Expr* CreateAdditionExpr( Expr*, Expr* );
    static Expr* CreateSubtractionExpr( Expr*, Expr* );
    static Expr* CreateMultiplicationExpr( Expr*, Expr* );
    static Expr* CreateDivisionExpr( Expr*, Expr* );

    static void DestroyExpr( Expr* );

protected:
    Expr();
    virtual ~Expr();
};

}

#endif

