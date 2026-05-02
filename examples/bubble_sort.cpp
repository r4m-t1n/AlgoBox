#include <iostream>
#include "algobox.hpp"

int bubble_sort(algobox::core<int>& c){
    for (int i=0; i<c.v.size()-1; i++){
        for (int j=0; j<c.v.size()-i-1; j++){
            if (c.v[j] > c.v[j+1]){
                c.v.swap(j, j+1);
            }
        }
    }
    return 0;
}

int main(){
    algobox::core<int> c;
    c.v = {10, 2, 3, 15, 12, 13, 5, 9, 10, 10, 19, 6, 14};
    algobox::algo_sort(bubble_sort, c);
    std::cin.get();
    
}