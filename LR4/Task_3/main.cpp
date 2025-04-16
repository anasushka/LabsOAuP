#include <iostream>
#include <vector>
#include "sort.h"

using namespace std;

int main(){
    vector <int> a = { 1, 5, 1, 4, 5, 6, 2, 1, 3, 4, 4, 4, 5, 7 };
    vector <double> b;

    int n= a.size();

    for(int i=0; i < n; i += 3){
        int count = n- i;
        if(count>=3){
            vector<int> group={a[i],a[i+1],a[i+2]};
            heapSort(group);
            double median=group[1];
            b.push_back(median);
        }else{
            double sum=0;
            for (int j=0; j<count ;++j){
                sum+=a[i+j];
            }
            double medium=sum/count;
            b.push_back(medium);
        }

    }
    for (int x : b)
        cout << x << " ";
    cout << endl;
}