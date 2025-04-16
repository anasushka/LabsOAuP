#include <iostream>


void hanoi(int n,char from, char help ,char to){
    if(n==1){
        std::cout <<"Перемещаем 1 кольцо из " <<from << " в " << to << '\n';
        return;
    }

    hanoi(n-1,from,to,help);

    std::cout <<"Перемещаем кольцо " << n << " из " << from << " в " << to << '\n';

    hanoi(n-1,help,from,to);
}

int main(){
    int n;
    std::cout<< "Ведите количество кольц : ";
    std::cin >> n;
    hanoi(n,'A','B','C');


    return 0;
}