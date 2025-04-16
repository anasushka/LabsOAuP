#include <iostream>
#include <string>

std::string toBinary(int n){
    if(n==0){
        return "";
    }if(n%2==1){
        return toBinary(n/2)+'1';
    }if(n%2==0){
        return toBinary(n/2)+'0';
    }
}

int main() {

    int number;

    std::cout <<"Введиет число которое хотите перевести в двоичную систему : ";
    std::cin >> number;

    std::string result= toBinary(number);
    std::cout << "Число "<<number<<" в двоичной системе : "<<result;

    return 0;
}
