#include "sort.h"
#include <algorithm>

void heapify(std::vector<int>& arr, int n, int i) {
    // Находим наибольший элемент среди корня, левого и правого потомка
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если корень не является наибольшим, меняем местами и продолжаем "просеивание"
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Функция пирамидальной сортировки для вектора
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);  // перемещаем текущий корень в конец
        heapify(arr, i, 0);
    }
}



