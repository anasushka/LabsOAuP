#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H
#include "expression.h"

class BinaryOperation:public Expression
{
public:
    BinaryOperation(Expression* l, char op, Expression* r);
    ~BinaryOperation() override;

    double evaluate() const override;

    int ExpressionType() const override;

private:
    Expression* left;
    Expression* right;
    char operation;
};

#endif // BINARYOPERATION_H
