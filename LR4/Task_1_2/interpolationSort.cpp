#include <iostream>
#include <cmath>
#include "sorts.h"

using namespace std;

void printArray(const vector<int>& A) {
    for (int x : A)
        cout << x << " ";
    cout << endl;
}

void divide(vector <int>& A, vector <int>& divideSize, int& end){
    int size =divideSize.back();
    divideSize.pop_back();

    int start=end-size;
    int min= A[start];
    int max=A[start];

    for (int i=start+1;i <end; i++){
        if(A[i]<min)
            min=A[i];
        if(A[i]>max)
            max=A[i];

    }

    if(min==max){
        end -=size;
        printArray(A);
        return;
    }

    vector<vector<int>> bucket(size);

    for (int i = start; i < end; i++) {
        int p = static_cast<int>(floor(((A[i] - min) * 1.0 / (max - min)) * (size - 1)));
        bucket[p].push_back(A[i]);
    }

    for (int i=0;i<size;i++){
        if (!bucket[i].empty()){
            for(int j=0; j <bucket[i].size();j++){
                A[start++]=bucket[i][j];
            }
            divideSize.push_back(bucket[i].size());
        }

    }
    printArray(A);
}

void interpolationSort(vector<int>& A) {
    int n = A.size();
    // divideSize хранит размеры сегментов для дальнейшей обработки
    vector<int> divideSize;
    divideSize.push_back(n);

    // Переменная end указывает на конец текущей области сортировки (изначально весь массив)
    int end = n;

    // Выполняем алгоритм до тех пор, пока не обработаны все сегменты
    while (!divideSize.empty()) {
        divide(A, divideSize, end);
    }
}


