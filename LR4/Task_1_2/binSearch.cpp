#include "sorts.h"


int binSearch(const std::vector<int>& arr, int target) {
    int size = arr.size();
    if(size == 0)
        return -1;
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int m = left + (right - left) / 2;  // корректный расчёт среднего индекса
        if (arr[m] == target) {
            return m;
        } else if (arr[m] < target) {
            left = m + 1;
        } else { // arr[m] > target
            right = m - 1;
        }
    }
    return -1;
}