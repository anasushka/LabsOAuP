#include "sorts.h"
#include <algorithm>



int partition(std::vector<int>& aArray, int aL, int aR) {
    int i = aL - 1;
    int j = aR;
    int p = aArray[aR];  // Опорный элемент
    for(;;) {
        while(aArray[++i] < p)
            ;
        while(p < aArray[--j])
            if(j == aL)
                break;
        if (i >= j)
            break;
        std::swap(aArray[i], aArray[j]);
    }
    std::swap(aArray[i], aArray[aR]);
    return i;
}

void quickSort(std::vector<int>& aArray, int aL, int aR) {
    if(aR <= aL)
        return;
    int i = partition(aArray, aL, aR);
    quickSort(aArray, aL, i - 1);
    quickSort(aArray, i + 1, aR);
}
