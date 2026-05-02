#include <iostream>
#include "algobox.hpp"


int linear_search(algobox::core<int>& c, int target, int n){
    if (n < 0) return -1;
    if (c.v[n] == target) return n;
    c++;
    return linear_search (c, target, n-1);
}

int main(){
    algobox::core<int> c;
    c.v = {1, 5, 7, 10, 12, 15, 17, 20, 23, 26, 30, 40, 43}; // it should be sorted first
    int target = 15;
    algobox::algo_search(linear_search, c, target, c.v.size()-1);
    std::cin.get();
}