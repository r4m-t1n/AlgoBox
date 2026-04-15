#pragma once

#include <vector>
#include <queue>
#include <thread>

namespace algobox{
    template <typename T>
    class vector;
    
    template <typename Func, typename... Args>
    auto algo_search(Func algorithm, Args&&... args);
};


template <typename T>
void screen_search(algobox::vector<T>& v, T target);

template <typename Func, typename... Args>
auto algobox::algo_search(Func algorithm, Args&&... args){
    auto result = algorithm(std::forward<Args>(args)...);

    auto params = std::forward_as_tuple(std::forward<Args>(args)...);

    using vector_type = std::decay_t<decltype(std::get<0>(params))>;
    using T = typename vector_type::value_type;

    algobox::vector<T>& v = std::get<0>(params);
    auto target = std::get<1>(params);

    std::thread gui_thread([&v, target](){
        screen_search<T>(v, target);
    });
    gui_thread.detach();

    return result;
}

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
            T val = this->at(index);

            nodes.push(index); // for now, to be implemented
            return std::vector<T>::operator[](index);
        }

        const T& operator[](size_t index) const{
            nodes.push(index);

            return std::vector<T>::operator[](index);
        }
};