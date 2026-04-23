#include <iostream>
#include "algobox_vector.hpp"
#include "gui.hpp"


int linear_search(algobox::vector<int>& v, int target){
    algobox::tracker loop(v);
    for (int i=0; i<v.size(); i++){
        if (v[i] == target) return i;
        loop++;
    }
    return -1;
}

int main(){
    algobox::vector<int> v = {1, 5, 7, 10, 12, 15, 17, 20, 23, 26, 30, 40, 43}; // it should be sorted first
    int target = 50;
    algobox::algo_search(linear_search, v, target);
    std::cin.get();
}