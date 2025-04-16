#include <iostream>

int A(int m, int n){
    if(m==0){
        return n+1;
    }else if(m>0 && n==0){
        return A(m-1,1);
    }else if(m>0 && n>0){
        return A(m-1,A(m,n-1));
    }
    return 1;
}

int main(){
    int m,n;
    std::cout<< "Ведите число m : ";
    std::cin >> m;
    std::cout<< "Ведите число n : ";
    std::cin >> n;

    int result = A(m,n);
    std::cout << "Результат A(n,m) = " << result;


    return 0;
}