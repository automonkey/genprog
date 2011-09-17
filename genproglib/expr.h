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
    /// Returned object takes ownership of supplied Expr obects
    static Expr* CreateAdditionExpr( Expr*, Expr* );
    /// Returned object takes ownership of supplied Expr obects
    static Expr* CreateSubtractionExpr( Expr*, Expr* );
    /// Returned object takes ownership of supplied Expr obects
    static Expr* CreateMultiplicationExpr( Expr*, Expr* );
    /// Returned object takes ownership of supplied Expr obects
    static Expr* CreateDivisionExpr( Expr*, Expr* );

    static void DestroyExpr( Expr* );

protected:
    Expr();
    virtual ~Expr();
};

void Swap( Expr*, Expr* );

}

#endif

