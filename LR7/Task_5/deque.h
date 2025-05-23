#ifndef TASK5_DEQUE_H
#define TASK5_DEQUE_H

#include <cstring>
#include <stdexcept>

template<typename T>
class Deque {
private:
    static const size_t block_size = 4;

    T** map;
    size_t map_capacity;

    size_t start_block, start_index;
    size_t end_block, end_index;

    size_t size_;

    T* allocate_block();
    void resize_map();

public:
    // Конструкторы и деструктор
    Deque();
    ~Deque();

    // Основные операции
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();

    // Доступ к элементам
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Информация о состоянии
    size_t size() const;
    bool empty() const;
    void clear();

    // Итератор без инвалидации
    class iterator {
    private:
        Deque<T>* deque_ptr;
        size_t logical_index;  // логический индекс от 0 до size-1

    public:
        iterator(Deque<T>* deque, size_t index) : deque_ptr(deque), logical_index(index) {}

        // Операторы сравнения
        bool operator==(const iterator& other) const {
            return deque_ptr == other.deque_ptr && logical_index == other.logical_index;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        // Операторы инкремента/декремента
        iterator& operator++() {
            logical_index++;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            logical_index++;
            return temp;
        }

        iterator& operator--() {
            logical_index--;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            logical_index--;
            return temp;
        }

        // Арифметические операторы
        iterator operator+(int n) const {
            return iterator(deque_ptr, logical_index + n);
        }

        iterator operator-(int n) const {
            return iterator(deque_ptr, logical_index - n);
        }

        int operator-(const iterator& other) const {
            return logical_index - other.logical_index;
        }

        iterator& operator+=(int n) {
            logical_index += n;
            return *this;
        }

        iterator& operator-=(int n) {
            logical_index -= n;
            return *this;
        }

        // Разыменование
        T& operator*() {
            return (*deque_ptr)[logical_index];
        }

        const T& operator*() const {
            return (*deque_ptr)[logical_index];
        }

        T* operator->() {
            return &((*deque_ptr)[logical_index]);
        }

        const T* operator->() const {
            return &((*deque_ptr)[logical_index]);
        }

        // Индексация
        T& operator[](int n) {
            return (*deque_ptr)[logical_index + n];
        }

        const T& operator[](int n) const {
            return (*deque_ptr)[logical_index + n];
        }
    };

    // Методы для получения итераторов
    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, size_);
    }
};

// Реализация методов

template<typename T>
Deque<T>::Deque() : size_(0), map_capacity(8), start_block(map_capacity / 2),
    end_block(map_capacity / 2), start_index(0), end_index(0) {
    map = new T*[map_capacity];
    memset(map, 0, map_capacity * sizeof(T*));
    map[start_block] = allocate_block();
}

template<typename T>
Deque<T>::~Deque() {
    for (size_t i = 0; i < map_capacity; i++) {
        if (map[i]) {
            delete[] map[i];
        }
    }
    delete[] map;
}

template<typename T>
T* Deque<T>::allocate_block() {
    return new T[block_size];
}

template<typename T>
void Deque<T>::resize_map() {
    size_t old_capacity = map_capacity;
    size_t old_start_block = start_block;
    size_t old_end_block = end_block;
    T** old_map = map;

    size_t new_capacity = old_capacity * 2;
    T** new_map = new T*[new_capacity];
    memset(new_map, 0, new_capacity * sizeof(T*));

    size_t blocks_in_use = old_end_block - old_start_block + 1;
    size_t new_start_block = (new_capacity - blocks_in_use) / 2;

    // Копируем указатели на блоки (не сами данные!)
    memcpy(new_map + new_start_block, old_map + old_start_block, blocks_in_use * sizeof(T*));

    start_block = new_start_block;
    end_block = start_block + blocks_in_use - 1;
    map = new_map;
    map_capacity = new_capacity;

    delete[] old_map;  // Удаляем только массив указателей, не сами блоки
}

template<typename T>
void Deque<T>::push_back(const T& value) {
    if (end_index >= block_size) {
        if (end_block + 1 >= map_capacity) {
            resize_map();
        }
        end_block++;
        end_index = 0;
        if (map[end_block] == nullptr) {
            map[end_block] = allocate_block();
        }
    }
    map[end_block][end_index++] = value;
    size_++;
}

template<typename T>
void Deque<T>::push_front(const T& value) {
    if (start_index <= 0) {
        if (start_block == 0) {
            resize_map();
        }
        start_block--;
        start_index = block_size;
        if (map[start_block] == nullptr) {
            map[start_block] = allocate_block();
        }
    }
    map[start_block][--start_index] = value;
    size_++;
}

template<typename T>
void Deque<T>::pop_back() {
    if (size() == 0) {
        throw std::out_of_range("pop_back called on empty deque");
    }
    if (end_index > 0) {
        end_index--;
    } else {
        end_block--;
        end_index = block_size - 1;
    }
    size_--;
}

template<typename T>
void Deque<T>::pop_front() {
    if (size() == 0) {
        throw std::out_of_range("pop_front called on empty deque");
    }
    if (start_index + 1 < block_size) {
        start_index++;
    } else {
        start_block++;
        start_index = 0;
    }
    size_--;
}

template<typename T>
T& Deque<T>::operator[](size_t index) {
    if (index >= size()) {
        throw std::out_of_range("Index out of range");
    }
    size_t offset = start_index + index;
    size_t block_offset = offset / block_size;
    size_t element_index = offset % block_size;
    return map[start_block + block_offset][element_index];
}

template<typename T>
const T& Deque<T>::operator[](size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("Index out of range");
    }
    size_t offset = start_index + index;
    size_t block_offset = offset / block_size;
    size_t element_index = offset % block_size;
    return map[start_block + block_offset][element_index];
}

template<typename T>
size_t Deque<T>::size() const {
    return size_;
}

template<typename T>
bool Deque<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void Deque<T>::clear() {
    // Не удаляем блоки, просто сбрасываем указатели и размер
    start_block = map_capacity / 2;
    end_block = start_block;
    start_index = 0;
    end_index = 0;
    size_ = 0;
}

#endif //TASK5_DEQUE_H
