#pragma once

#include <vector>
#include <queue>
#include "algobox.hpp"


template <typename T>
class algobox::vector: public std::vector<T>{
    public:
        static_assert(std::is_arithmetic_v<T>, "You should use number data types.");

        using std::vector<T>::vector;

        mutable std::queue<size_t> nodes;

        T get_max(){
            if (this->empty())
                return 0;

            T m = this->at(0);
            for (int i=0; i<this->size(); i++){
                if (this->at(i) > m) m = this->at(i);
            }
            return m;
        }

        T& operator[](size_t index){
            nodes.back() = index; // for now, to be implemented
            return std::vector<T>::operator[](index);
        }

        const T& operator[](size_t index) const{
            nodes.back() = index;

            return std::vector<T>::operator[](index);
        }
};