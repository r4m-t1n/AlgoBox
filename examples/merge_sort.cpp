#include <iostream>
#include "algobox.hpp"

template <typename T>
void merge(algobox::core<T>& c, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> l(n1), r(n2);

    for (int i=0; i < n1; i++)
        l[i] = c.v[left + i];

    for (int j=0; j < n2; j++)
        r[j] = c.v[mid + 1 + j];

    int i=0;
    int j=0;
    int k=left;

    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            c.v[k]=l[i];
            i++;
        } else {
            c.v[k]=r[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        c.v[k]=l[i];
        i++;
        k++;
    }

    while (j < n2) {
        c.v[k]=r[j];
        j++;
        k++;
    }
}

template <typename T>
void merge_sort_recursive(algobox::core<T>& c, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort_recursive(c, left, mid);
    merge_sort_recursive(c, mid + 1, right);

    merge(c, left, mid, right);
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

    algobox::algo_sort(merge_sort_recursive<int>, c, 0, (int)c.v.size() - 1);
    std::cin.get();

}