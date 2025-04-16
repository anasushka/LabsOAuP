#include "binaryoperation.h"
#include <stdexcept>

BinaryOperation::BinaryOperation(Expression* l, char op, Expression* r):left(l),operation(op),right(r)
{}


BinaryOperation::~BinaryOperation() {
    delete left;
    delete right;
}

double BinaryOperation::evaluate() const {
    double l=left->evaluate();
    double r=right->evaluate();

    switch (operation) {
    case '+':
        return l+r;
    case '-':
        return l-r;
    case '*':
        return l*r;
    case '/':
        if(r==0)
        throw std::runtime_error("Нельзя делить на 0");
        return l/r;
    default:
        throw std::runtime_error("Что-то не то ввели...");
    }
}

int BinaryOperation::ExpressionType() const {
    return 1;
};
