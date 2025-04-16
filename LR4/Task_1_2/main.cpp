#include "sorts.h"
#include <iostream>

int main() {

    std::vector<int> arr = {2, 4, 5, 1, 6, 12, 14, 7, 8};

    std::cout << "Исходный вектор:" << std::endl;
    printArray(arr);


    std::vector<int> quickSorted = arr;
    quickSort(quickSorted, 0, quickSorted.size() - 1);
    std::cout << "\nПосле quickSort:" << std::endl;
    printArray(quickSorted);
    measureSortTime("quickSort", arr, quickSort);


    std::vector<int> heapSorted = arr;
    heapSort(heapSorted);
    std::cout << "\nПосле heapSort:" << std::endl;
    printArray(heapSorted);
    measureSimpleSortTime("heapSort", arr, heapSort);


    std::vector<int> mergeSorted = arr;
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    std::cout << "\nПосле mergeSort:" << std::endl;
    printArray(mergeSorted);
    measureSortTime("mergeSort", arr, mergeSort);



    std::vector<int> interpolationSorted = arr;
    std::cout << "\n\nКаждый шаг interpolationSort:" << std::endl;
    interpolationSort(interpolationSorted);
    measureSimpleSortTime("interpolationSort", arr, interpolationSort);



    std::cout << "\nВведите число для поиска: ";
    int target;
    std::cin >> target;
    int idx = binSearch(mergeSorted, target);
    if(idx != -1) {
        std::cout << "Найденный элемент: " << mergeSorted[idx] << " на позиции " << idx << std::endl;
    } else {
        std::cout << "Элемент не найден." << std::endl;
    }

    std::cout << "\nВведите значение mod: ";
    int mod;
    std::cin >> mod;

    // Вычисляем: (индекс найденного элемента)^(длина вектора) mod mod
    int poweredIndex = binpow(idx, arr.size(), mod);
    std::cout << "\nРезультат binpow(" << idx << ", " << arr.size() << ", " << mod << ") = " << poweredIndex << std::endl;



    return 0;
}

