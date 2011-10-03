#include "expr.h"

#include <tr1/memory>
#include <stdexcept>

namespace
{

typedef std::tr1::shared_ptr< genproglib::Expr > ExprPtr;

}

namespace genproglib
{

Expr::Expr()
{
}

Expr::~Expr()
{
}

class BinaryExpr;

class ExprImpl : public Expr
{
public:
    ExprImpl()
        : mParent( 0 )
    {
    }

    void SetParent( BinaryExpr* parent )
    {
        mParent = parent;
    }

    void Swap( ExprImpl& );

protected:
    ~ExprImpl()
    {
    }

private:
    /// gets, from the parent, the child node ptr that points
    /// to the supplied ExprImpl
    static ExprPtr& GetChildPtrOfParent( ExprImpl& );

    // parents must by definition be binary expr nodes
    BinaryExpr* mParent;
};

class LiteralExpr : public ExprImpl
{
public:
    explicit LiteralExpr( EXPR_VAL );

    EXPR_VAL Evaluate() const;

protected:
    ~LiteralExpr()
    {
    }

private:
    EXPR_VAL mVal;
};

LiteralExpr::LiteralExpr( EXPR_VAL val )
    : mVal( val )
{
}

EXPR_VAL LiteralExpr::Evaluate() const
{
    return mVal;
}

class BinaryExpr : public ExprImpl
{
public:
    BinaryExpr( ExprImpl* op1, ExprImpl* op2 )
        : mOp1( op1, Expr::DestroyExpr )
        , mOp2( op2, Expr::DestroyExpr )
    {
        op1->SetParent( this );
        op2->SetParent( this );
    }

    ExprPtr mOp1;
    ExprPtr mOp2;

protected:
    ~BinaryExpr()
    {
    }
};

#define DEFINE_BINARY_OPERATOR_EXPR( EXPR_NAME )                \
class EXPR_NAME : public BinaryExpr                             \
{                                                               \
public:                                                         \
    EXPR_NAME( ExprImpl* op1, ExprImpl* op2 )                   \
        : BinaryExpr( op1, op2 )                                \
    {                                                           \
    }                                                           \
                                                                \
    EXPR_VAL Evaluate() const;                                  \
                                                                \
protected:                                                      \
    ~EXPR_NAME()                                                \
    {                                                           \
    }                                                           \
};

DEFINE_BINARY_OPERATOR_EXPR( AdditionExpr ) 
EXPR_VAL AdditionExpr::Evaluate() const
{
    return mOp1->Evaluate() + mOp2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( SubtractionExpr ) 
EXPR_VAL SubtractionExpr::Evaluate() const
{
    return mOp1->Evaluate() - mOp2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( MultiplicationExpr ) 
EXPR_VAL MultiplicationExpr::Evaluate() const
{
    return mOp1->Evaluate() * mOp2->Evaluate();
}

DEFINE_BINARY_OPERATOR_EXPR( DivisionExpr ) 
EXPR_VAL DivisionExpr::Evaluate() const
{
    return mOp1->Evaluate() / mOp2->Evaluate();
}

Expr* Expr::CreateLiteralExpr( EXPR_VAL val )
{
    return new LiteralExpr( val );
}

Expr* Expr::CreateAdditionExpr( Expr* op1, Expr* op2 )
{
    return new AdditionExpr(
        static_cast< ExprImpl* >( op1 ),
        static_cast< ExprImpl* >( op2 )
    );
}

Expr* Expr::CreateSubtractionExpr( Expr* op1, Expr* op2 )
{
    return new SubtractionExpr(
        static_cast< ExprImpl* >( op1 ),
        static_cast< ExprImpl* >( op2 )
    );
}

Expr* Expr::CreateMultiplicationExpr( Expr* op1, Expr* op2 )
{
    return new MultiplicationExpr(
        static_cast< ExprImpl* >( op1 ),
        static_cast< ExprImpl* >( op2 )
    );
}

Expr* Expr::CreateDivisionExpr( Expr* op1, Expr* op2 )
{
    return new DivisionExpr(
        static_cast< ExprImpl* >( op1 ),
        static_cast< ExprImpl* >( op2 )
    );
}

void Swap( Expr* expr1, Expr* expr2 )
{
    ExprImpl* exprImpl1 = static_cast< ExprImpl* >( expr1 );
    ExprImpl* exprImpl2 = static_cast< ExprImpl* >( expr2 );

    exprImpl1->Swap( *exprImpl2 );
}

ExprPtr& ExprImpl::GetChildPtrOfParent( ExprImpl& child )
{
    BinaryExpr* parent = child.mParent;

    if( parent->mOp1.get() == &child )
    {
        return parent->mOp1;
    }
    else if( parent->mOp2.get() == &child )
    {
        return parent->mOp2;
    }

    throw std::runtime_error( "Node is not a child of it's parent?!" );
}

void ExprImpl::Swap( ExprImpl& other )
{
    // node position dictated by ownership to parent - swap parent child
    // node ptrs in parents
    ExprPtr& thisParentChildPtr = GetChildPtrOfParent( *this );
    ExprPtr& otherParentChildPtr = GetChildPtrOfParent( other );
    thisParentChildPtr.swap(otherParentChildPtr);

    std::swap( mParent, other.mParent );
}

void Expr::DestroyExpr( Expr* expr )
{
    delete expr;
}

}

