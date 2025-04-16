#ifndef NUMBER_H
#define NUMBER_H
#include "expression.h"


class Number:public Expression
{
public:
    Number(double value);
    ~Number() override= default;

    double evaluate() const  override;

    int ExpressionType() const override;
private:
    double value;
};

#endif // NUMBER_H
