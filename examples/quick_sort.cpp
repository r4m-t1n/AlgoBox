#include <iostream>
#include "algobox.hpp"

template <typename T>
int partition(algobox::core<T>& c, int low, int high) {
    T pivot = c.v[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (c.v[j] < pivot) {
            i++;
            c.v.swap(i, j);
        }
    }
    c.v.swap(i + 1, high);
    return i + 1;
}

template <typename T>
void quick_sort_recursive(algobox::core<T>& c, int low, int high) {
    if (low < high) {
        int pi = partition(c, low, high);

        quick_sort_recursive(c, low, pi - 1);
        quick_sort_recursive(c, pi + 1, high);
    }
}

int main(){
    algobox::core<int> c({
        42, 17, 89, 3, 56, 72, 11, 95, 24, 68,
        7, 33, 51, 82, 14, 99, 45, 6, 29, 61,
        77, 10, 53, 38, 91, 19, 84, 5, 66, 48,
        90, 12, 36, 74, 2, 59, 21, 88, 31, 65,
        80, 55, 9, 43, 27, 71, 98, 15, 63, 39,
        4, 87, 23, 52, 79, 13, 96, 46, 32, 60,
        75, 1, 37, 85, 20, 58, 93, 28, 64, 41,
        100, 18, 54, 70, 8, 44, 26, 81, 16, 92,
        35, 67, 49, 97, 22, 57, 83, 30, 62, 50,
        73, 25, 47, 86, 34, 78, 69, 40, 76, 94
    }, 0.005);
    algobox::algo_sort(quick_sort_recursive<int>, c, 0, (int)c.v.size() - 1);
    std::cin.get();

}