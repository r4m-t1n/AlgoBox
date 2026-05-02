#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include "algobox.hpp"


template <typename T>
class algobox::vector: public std::vector<T>{
    public:
        static_assert(std::is_arithmetic_v<T>, "You should use number data types.");

        AlgoMode mode;

        using std::vector<T>::vector;

        mutable std::queue<size_t> nodes;
        mutable std::queue<algobox::State<T>> copies;

        T get_max(){
            if (this->empty())
                return 0;

            T m = this->at(0);
            for (int i=0; i<this->size(); i++){
                if (this->at(i) > m) m = this->at(i);
            }
            return m;
        }

        void swap(size_t index_1, size_t index_2){
            if (index_1 >= this->size() || index_2 >= this->size())
                return;

            size_t tmp = this->at(index_1);
            size_t tmp_2 = this->at(index_2);
            this->at(index_1) = this->at(index_2);
            this->at(index_2) = tmp;
            copies.emplace(std::vector<T>(*this), index_2, index_2, index_1); // green, red
        }

        T& operator[](size_t index){
            switch (mode) {
                case SEARCH:
                    if (nodes.empty()){
                        nodes.push(index);
                    }
                    nodes.back() = index;
                    break;
                
                case SORT:
                    size_t empty_element = static_cast<size_t>(-1);
                    copies.emplace(std::vector<T>(*this), index, empty_element, empty_element);
                    break;
            }
            return std::vector<T>::operator[](index);
        }

        const T& operator[](size_t index) const{
            switch (mode) {
                case SEARCH:
                    if (nodes.empty()){
                        nodes.push(index);
                    }
                    nodes.back() = index;
                    break;
            }
            return std::vector<T>::operator[](index);
        }
};