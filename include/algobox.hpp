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

    inline static const size_t empty_element = static_cast<size_t>(-1);
};

enum AlgoMode {
    NONE,
    SEARCH,
    SORT,
    TREE,
    GRAPH
};

#include "exceptions.hpp"
#include "algobox_vector.hpp"
#include "algobox_dict.hpp"

template <typename T>
class algobox::core {
    public:
        using value_type = T;

        algobox::vector<T> v;
        algobox::dict vars;

        const size_t size_limit;

        const float screen_height;
        const float screen_width;

        float time;

        core(const algobox::vector<T>& vector, const algobox::dict& dict,
            const float height, const float width, const float loop_time);

        core(const std::initializer_list<T>& vector, const algobox::dict& dict,
            const float height, const float width, const float loop_time);

        core(const std::vector<T>& vector, const algobox::dict& dict,
            const float height, const float width, const float loop_time);

        core(const algobox::vector<T>& vector, const algobox::dict& dict,
            const float height, const float width);

        core(const algobox::vector<T>& vector, const algobox::dict& dict,
            const float loop_time);

        core(const algobox::vector<T>& vector, const algobox::dict& dict);

        core(const algobox::vector<T>& vector, const float loop_time);

        core(const algobox::vector<T>& vector);

        core(const std::vector<T>& vector);
        
        core(const std::initializer_list<T>& vector);

        core(const float loop_time);

        core();
        core<T>& operator=(const algobox::vector<T>& other);

        void operator++(int);

        const size_t& loop = _loop;

    private:

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
algobox::State<T>::State(const std::vector<T>& v, const size_t i, const size_t s_1, const size_t s_2):
    data(v), index(i), swap_1(s_1), swap_2(s_2) {}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector, const algobox::dict& dict,
    const float height, const float width, const float loop_time) :
    v(vector.get_data_ptr(), vector.size(), vector.capacity(), vector.width_limit()), vars(dict),
    screen_height(height), screen_width(width), size_limit(static_cast<size_t>(width/2.0)),
    time(loop_time){
        v++;
        vars++;
}

template <typename T>
algobox::core<T>::core(const std::initializer_list<T>& vector, const algobox::dict& dict,
    const float height, const float width, const float loop_time) :
    v(vector.begin(), vector.size(), vector.size(), width), vars(dict),
    screen_height(height), screen_width(width), size_limit(static_cast<size_t>(width/2.0)),
    time(loop_time){
    v++;
    vars++;
}

template <typename T>
algobox::core<T>::core(const std::vector<T>& vector, const algobox::dict& dict,
    const float height, const float width, const float loop_time) :
    v(vector, vector.size(), vector.capacity(), width), vars(dict),
    screen_height(height), screen_width(width), size_limit(static_cast<size_t>(width/2.0)),
    time(loop_time){
    v++;
    vars++;
}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector, const algobox::dict& dict,
    const float height, const float width) :
    core(vector, dict, height, width, 1.0f) {}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector, const algobox::dict& dict,
    const float loop_time) :
    core(vector, dict, 720.0f, 720.0f, loop_time) {}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector, const algobox::dict& dict) :
    core(vector, dict, 720.0f, 720.0f, 1.0f) {}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector, const float loop_time) :
    core(vector, {}, 720.0f, 720.0f, loop_time) {}

template <typename T>
algobox::core<T>::core(const algobox::vector<T>& vector) :
    core(vector, {}, 720.0f, 720.0f, 1.0f) {}

template <typename T>
algobox::core<T>::core(const std::vector<T>& vector) :
    core(vector, {}, 720.0f, 720.0f, 1.0f) {}

template <typename T>
algobox::core<T>::core(const std::initializer_list<T>& vector) :
    core(vector, {}, 720.0f, 720.0f, 1.0f) {}

template <typename T>
algobox::core<T>::core(const float loop_time) :
    core({}, {}, 720.0f, 720.0f, loop_time) {}

template <typename T>
algobox::core<T>::core() :
    core({}, {}, 720.0f, 720.0f, 1.0f) {}

template <typename T>
algobox::core<T>& algobox::core<T>::operator=(const algobox::vector<T>& other){
    static_cast<algobox::vector<T>&>(v) = other;
    return *this;
}

template <typename T>
void algobox::core<T>::operator++(int){
    _loop++;
    if (v.mode == SEARCH){
        v++;
        vars++;
    }
    else if (v.mode == SORT){
        if (!vars.data.empty())
            vars++;
    }
}

template <typename T>
void screen_search(algobox::core<T>& c, const T target);

template <typename T>
void screen_sort(algobox::core<T>& c);

#include "handler.hpp"
#include "gui/utils.hpp"
#include "gui/screen_search.hpp"
#include "gui/screen_sort.hpp"