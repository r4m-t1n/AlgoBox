#pragma once

namespace algobox{
    
    template <typename T>
    class vector;
    
    class dict;

    template <typename T>
    class core;

    template <typename Func, typename... Args>
    auto algo_search(Func algorithm, Args&&... args);
};

#include "algobox_vector.hpp"
#include "algobox_dict.hpp"

template <typename T>
class algobox::core {
    public:
        using value_type = T;

        algobox::vector<T> v;
        algobox::dict vars;

        size_t loop = 0;

        const size_t empty_element = static_cast<size_t>(-1);

        core(const algobox::vector<T>& vector, const algobox::dict& dict);

        core(const algobox::vector<T>& vector);

        core();
        core<T>& operator=(const algobox::vector<T>& other);

        void operator++(int);

    private:
        void add_empty_element();

        void add_empty_element_v();
};

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector, const algobox::dict& dict) :
    v(vector), vars(dict){
        add_empty_element();
}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector)  :
    v(vector){
    add_empty_element_v();
}

template <typename T>
algobox::core<T>::core() : v(), vars(){
    add_empty_element();
}

template <typename T>
algobox::core<T>& algobox::core<T>::operator=(const algobox::vector<T>& other){
    static_cast<algobox::vector<T>&>(v) = other;
    return *this;
}

template <typename T>
void algobox::core<T>::operator++(int){
    loop++;            
    add_empty_element();
}

template <typename T>
void algobox::core<T>::add_empty_element(){
    for (auto& [key, val]: vars.data){
        if (val.empty())
            val.push(empty_element);
        else
            val.push(val.back());
    }
    v.nodes.push(empty_element);
}

template <typename T>
void algobox::core<T>::add_empty_element_v(){
    v.nodes.push(empty_element);
}

template <typename T>
void screen_search(algobox::core<T>& c, const T target);

#include "search_handler.hpp"
#include "gui.hpp"