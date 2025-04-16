#include <QCoreApplication>
#include "number.h"
#include "binaryoperation.h"
#include <iostream>

bool check_equals(Expression const* left, Expression const* right) {
    return left->ExpressionType() == right->ExpressionType();
}

int main(int argc, char *argv[])
{
    Expression* sube = new BinaryOperation(new Number(7), '*', new Number(5));
    Expression* expr = new BinaryOperation(new Number(3), '-', sube);
    std::cout << expr->evaluate() << std::endl;


    delete expr;
    Expression* a = new Number(4);
    Expression* b = new Number(5);
    Expression* c = new BinaryOperation(a, '*', b);
    std::cout << check_equals(a, b) << ' ' << check_equals(a, c) << '\n';
    return 0;
}
