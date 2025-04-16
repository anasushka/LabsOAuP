#ifndef LR4_SORTS_H
#define LR4_SORTS_H
#include <vector>
#include <chrono>


using namespace std;
using namespace std::chrono;

void quickSort(std::vector<int>& aArray, int aL, int aR);
void heapSort(std::vector<int>& arr);
void mergeSort(std::vector<int>& arr, int left, int right);

void interpolationSort(std::vector<int>& A);
int binpow(int digit,int powder, int mod);
void printArray(const std::vector<int>& A);

int binSearch(const std::vector<int>& arr,int target);

void measureSortTime(const string& name, vector<int> arr, void(*sortFunc)(vector<int>&, int, int));
void measureSimpleSortTime(const string& name, vector<int> arr, void(*sortFunc)(vector<int>&));

#endif //LR4_SORTS_H
