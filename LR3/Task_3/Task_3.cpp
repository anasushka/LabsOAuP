#include <iostream>


int reverse(int n, int rev){
    if(n==0){
        return rev;
    }
    int a=n%10;
    rev=rev*10+a;
    n=n/10;
    return reverse(n,rev);
}

int main(){
    int n;
    std::cout<< "Ведите число : ";
    std::cin >> n;

    int rev= reverse(n,0);
    std::cout << "Результат :  " << rev;

    return 0;
}