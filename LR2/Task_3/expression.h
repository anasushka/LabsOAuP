#ifndef EXPRESSION_H
#define EXPRESSION_H



class Expression
{
public:
    virtual ~Expression(){}

    virtual double evaluate() const =0;

    virtual int ExpressionType() const = 0;

};

#endif // EXPRESSION_H
