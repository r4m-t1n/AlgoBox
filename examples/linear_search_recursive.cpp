#include <iostream>
#include "algobox_vector.hpp"
#include "gui.hpp"


int linear_search(algobox::vector<int>& v, int target, int n, algobox::tracker<int>& loop){
    if (n < 0) return -1;
    if (v[n] == target) return n;
    loop++;
    return linear_search (v, target, n-1, loop);
}

int main(){
    algobox::vector<int> v = {1, 5, 7, 10, 12, 15, 17, 20, 23, 26, 30, 40, 43}; // it should be sorted first
    algobox::tracker<int> loop(v);
    int target = 15;
    algobox::algo_search(linear_search, v, target, v.size()-1, loop);
    std::cin.get();
}