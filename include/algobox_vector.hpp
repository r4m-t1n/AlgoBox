#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <thread>

namespace algobox{
    template <typename T>
    struct tracker;
    template <typename T>
    class vector;
    class dict;
    
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

class algobox::dict {
    public:
        mutable std::unordered_map<std::string, std::queue<size_t>> data;

        dict() : data() {};

        size_t& operator[](const std::string& key){
            std::queue<size_t>& val = data[key];
            if (val.empty()){
                val.push(0);
            }
            return val.back();
        }

        const size_t operator[](const std::string& key) const{
            if (data.find(key) == data.end() || data[key].empty())
                return 0;
            return data[key].back();
        }

};

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

            nodes.back() = index; // for now, to be implemented
            return std::vector<T>::operator[](index);
        }

        const T& operator[](size_t index) const{
            nodes.back() = index;

            return std::vector<T>::operator[](index);
        }
};

template <typename T>
class algobox::tracker{
    public:
        size_t loop_index = 0;

        tracker(algobox::vector<T>& v, algobox::dict& kv):
            vector(v), vars(kv) {

            add_empty_element();

        }
        tracker(algobox::vector<T>& v):
            vector(v), vars(dummy_dict) {

            add_empty_element_v();
        }

        void operator++(int){
            loop_index++;            
            add_empty_element();
        }
    private:
        algobox::vector<T>& vector;
        algobox::dict& vars;
        static inline algobox::dict dummy_dict;

        void add_empty_element(){
            const size_t empty_element = static_cast<size_t>(-1);
            for (auto& [key, val]: vars.data){
                val.push(empty_element);
            }
            vector.nodes.push(empty_element);
        }

        void add_empty_element_v(){
            const size_t empty_element = static_cast<size_t>(-1);

            vector.nodes.push(empty_element);
        }
};