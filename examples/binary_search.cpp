#include <iostream>
#include "algobox.hpp"


int binary_search(algobox::core<int>& c, int target){
    if (c.v.empty()) return -1;

    c.vars["low"] = 0;
    c.vars["high"] = c.v.size()-1;
    c++;
    while (c.vars["low"] <= c.vars["high"]){

        int mid = (c.vars["high"]+c.vars["low"]) / 2;

        if (c.v[mid] == target){
            return mid;
        } else if (c.v[mid] < target){
            c.vars["low"] = mid + 1;
        } else {
            c.vars["high"] = mid - 1;
        }
        c++;
    }

    return -1;
}

int main(){
    algobox::core<int> c;
    c.v = {
        1, 4, 7, 9, 12, 15, 18, 20, 22, 25, 28, 30, 33, 35, 38, 40, 42, 45, 48, 50,
        52, 55, 58, 60, 63, 66, 69, 71, 74, 77, 80, 82, 85, 88, 91, 93, 96, 99, 102, 105,
        108, 110, 113, 116, 119, 121, 124, 127, 130, 132, 135, 138, 141, 143, 146, 149, 152, 154, 157, 160,
        163, 166, 169, 171, 174, 177, 180, 182, 185, 188, 191, 194, 197, 200, 203, 206, 209, 212, 215, 218,
        221, 224, 227, 230, 233, 236, 239, 242, 245, 248, 251, 254, 257, 260, 263, 266, 269, 272, 275, 280
    }; // it should be sorted first
    int target = 251;
    algobox::algo_search(binary_search, c, target);
    std::cin.get();
}