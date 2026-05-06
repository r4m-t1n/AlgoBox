#pragma once

#include <iostream>
#include <unordered_map>
#include <queue>
#include "algobox.hpp"

class algobox::dict {
    public:
        mutable std::unordered_map<std::string, std::queue<size_t>> data;

        dict();

        size_t& operator[](const std::string& key);

        const size_t operator[](const std::string& key) const;

};

inline algobox::dict::dict(): data() {}

inline size_t& algobox::dict::operator[](const std::string& key){
    std::queue<size_t>& val = data[key];
    if (val.empty()){
        val.push(0);
    }
    return val.back();
}

inline const size_t algobox::dict::operator[](const std::string& key) const{
    if (data.find(key) == data.end() || data[key].empty())
        return 0;
    return data[key].back();
}