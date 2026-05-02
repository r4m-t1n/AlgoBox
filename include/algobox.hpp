#pragma once

namespace algobox{
    
    template <typename T>
    class vector;
    
    class dict;

    template <typename T>
    class core;

    template <typename T>
    struct State;

    template <typename Func, typename... Args>
    auto algo_search(Func algorithm, Args&&... args);

    template <typename Func, typename... Args>
    auto algo_sort(Func algorithm, Args&&... args);
};

enum AlgoMode {
    SEARCH,
    SORT,
    TREE,
    GRAPH
};

#include "algobox_vector.hpp"
#include "algobox_dict.hpp"

template <typename T>
class algobox::core {
    public:
        using value_type = T;

        algobox::vector<T> v;
        algobox::dict vars;

        inline static const size_t empty_element = static_cast<size_t>(-1);

        core(const algobox::vector<T>& vector, const algobox::dict& dict);

        core(const algobox::vector<T>& vector);

        core();
        core<T>& operator=(const algobox::vector<T>& other);

        void operator++(int);

        const size_t& loop = _loop;

    private:
        void add_empty_element();

        void add_empty_element_v();

        size_t _loop = 0;
};

template <typename T>
struct algobox::State {
    std::vector<T> data;
    size_t index;
    size_t swap_1;
    size_t swap_2;

    State(const std::vector<T>& v, const size_t i, const size_t s_1, const size_t s_2);
};

template <typename T>
algobox::State<T>::State(const std::vector<T>& v, const size_t i, const size_t s_1, const size_t s_2): data(v), index(i), swap_1(s_1), swap_2(s_2) {}

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
    _loop++;
    if (v.mode == SEARCH)
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

template <typename T>
void screen_sort(algobox::core<T>& c);

#include "handler.hpp"
#include "gui/utils.hpp"
#include "gui/screen_search.hpp"
#include "gui/screen_sort.hpp"