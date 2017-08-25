#ifndef LIBUT_TESTMATCHERS
#define LIBUT_TESTMATCHERS

template <class OPERATOR>
class OperatorMatcher : public Catch::MatcherBase<Lib::ExprPtr> {

public:
    virtual bool match( Lib::ExprPtr const& expr ) const override {
        return dynamic_cast<OPERATOR*>(expr.get()) != NULL;
    }

    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is " << OperatorName() << " operator object";
        return ss.str();
    }

    std::string OperatorName() const;
};

template<>
std::string OperatorMatcher<Lib::AdditionExpr>::OperatorName() const {
    return "addition";
}

template<>
std::string OperatorMatcher<Lib::SubtractionExpr>::OperatorName() const {
    return "subtraction";
}

template<>
std::string OperatorMatcher<Lib::MultiplicationExpr>::OperatorName() const {
    return "multiplication";
}

template<>
std::string OperatorMatcher<Lib::DivisionExpr>::OperatorName() const {
    return "division";
}

template<>
std::string OperatorMatcher<Lib::LiteralExpr>::OperatorName() const {
    return "literal";
}

template<>
std::string OperatorMatcher<Lib::Input>::OperatorName() const {
    return "input";
}

inline OperatorMatcher<Lib::AdditionExpr> IsAdditionOperator() {
    return OperatorMatcher<Lib::AdditionExpr>();
}

inline OperatorMatcher<Lib::SubtractionExpr> IsSubtractionOperator() {
    return OperatorMatcher<Lib::SubtractionExpr>();
}

inline OperatorMatcher<Lib::MultiplicationExpr> IsMultiplicationOperator() {
    return OperatorMatcher<Lib::MultiplicationExpr>();
}

inline OperatorMatcher<Lib::DivisionExpr> IsDivisionOperator() {
    return OperatorMatcher<Lib::DivisionExpr>();
}

inline OperatorMatcher<Lib::LiteralExpr> IsLiteral() {
    return OperatorMatcher<Lib::LiteralExpr>();
}

inline OperatorMatcher<Lib::Input> IsInput() {
    return OperatorMatcher<Lib::Input>();
}

#endif
