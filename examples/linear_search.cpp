#include <iostream>
#include "algobox.hpp"


int linear_search(algobox::core<int>& c, int target){
    for (int i=0; i<c.v.size(); i++){
        if (c.v[i] == target) return i;
        c++;
    }
    return -1;
}

int main(){
    algobox::core<int> c;
    c.v = {1, 5, 7, 10, 12, 15, 17, 20, 23, 26, 30, 40, 43}; // it should be sorted first
    int target = 50;
    algobox::algo_search(linear_search, c, target);
    std::cin.get();
}