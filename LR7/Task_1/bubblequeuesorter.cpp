#include "bubblequeuesorter.h"
#include <vector>

void BubbleQueueSorter::sort(IQueue& queue) {
    if (queue.size() < 2) return;

    // Извлекаем все элементы из очереди
    std::vector<int> elements;
    while (!queue.isEmpty()) {
        elements.push_back(queue.dequeue());
    }

    // Сортируем пузырьком
    int n = elements.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (elements[j] > elements[j + 1]) {
                // Меняем местами соседние элементы
                int temp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = temp;
                swapped = true;
            }
        }
        // Если за проход не было обменов, массив отсортирован
        if (!swapped) break;
    }

    // Возвращаем отсортированные элементы в очередь
    for (int element : elements) {
        queue.enqueue(element);
    }
}
