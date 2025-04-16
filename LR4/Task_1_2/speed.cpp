#include <iostream>

#include "sorts.h"



// Функция для измерения времени сортировки с аргументами (vector, left, right)
void measureSortTime(const string& name, vector<int> arr, void(*sortFunc)(vector<int>&, int, int)) {
    auto start = high_resolution_clock::now();

    sortFunc(arr, 0, arr.size() - 1);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << name << " заняла: " << duration.count() << " мкс" << endl;
}

// Функция для измерения сортировок с одним аргументом (heapSort, interpolationSort и т.п.)
void measureSimpleSortTime(const string& name, vector<int> arr, void(*sortFunc)(vector<int>&)) {
    auto start = high_resolution_clock::now();

    sortFunc(arr);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << name << " заняла: " << duration.count() << " мкс" << endl;
}
