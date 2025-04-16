#include "sorts.h"

void merge(std::vector<int>& arr, int left, int m, int right) {
    int n1 = m - left + 1;
    int n2 = right - m;

    // Временные векторы для хранения левой и правой частей
    std::vector<int> L(n1), M(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = left;
    // Слияние временных векторов обратно в arr
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = M[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = M[j++];
    }
}
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int m = left + (right - left) / 2;
        mergeSort(arr, left, m);
        mergeSort(arr, m + 1, right);
        merge(arr, left, m, right);
    }
}
