cmake_minimum_required(VERSION 3.30)
project(LR4)

set(CMAKE_CXX_STANDARD 26)

add_executable(Task_1 Task_1_2/main.cpp
        Task_1_2/quickSort.cpp
        Task_1_2/heapSort.cpp
        Task_1_2/binSearch.cpp
        Task_1_2/mergeSort.cpp
        Task_1_2/interpolationSort.cpp
        Task_1_2/binpow.cpp
        Task_1_2/speed.cpp
)


add_executable(Task_3 Task_3/main.cpp
        Task_3/sort.cpp
)