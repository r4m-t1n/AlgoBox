#include <iostream>
#include "algobox.hpp"

void selection_sort(algobox::core<int>& c){
    for (int i=0; i<c.v.size()-1; i++){
        c.vars["min"] = i;
        c++;
        for (int j=i+1; j<c.v.size(); j++){
            if (c.v[j] < c.v.at(c.vars["min"])){
                c.vars["min"] = j;
            }
            c++;
        }
        c.v.swap(c.vars["min"], i);
    }
}

int main(){
    algobox::core<int> c;
    c.v = algobox::vector {
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
    };
    c.time = 0.005;
    algobox::algo_sort(selection_sort, c);
    std::cin.get();
    
}