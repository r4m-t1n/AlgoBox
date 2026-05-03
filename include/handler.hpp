#pragma once

#include <thread>
#include "algobox.hpp"

template <typename Func, typename... Args>
auto algobox::algo_search(Func algorithm, Args&&... args){
    
    auto params = std::forward_as_tuple(std::forward<Args>(args)...);
    
    using first_arg = std::decay_t<std::tuple_element_t<0, std::tuple<Args...>>>;
    using T = typename first_arg::value_type;
    
    algobox::core<T>& c = std::get<0>(params);
    auto target = std::get<1>(params);

    c.v.mode = SEARCH;

    if (c.v.size() > c.size_limit)
        throw SizeLimitException(c.v.size(), c.size_limit);
    
    auto result = algorithm(std::forward<Args>(args)...);

    std::thread gui_thread([&c, target](){
        screen_search<T>(c, target);
    });
    gui_thread.detach();

    return result;
}

template <typename Func, typename... Args>
auto algobox::algo_sort(Func algorithm, Args&&... args){
    
    auto params = std::forward_as_tuple(std::forward<Args>(args)...);
    
    using first_arg = std::decay_t<std::tuple_element_t<0, std::tuple<Args...>>>;
    using T = typename first_arg::value_type;
    
    algobox::core<T>& c = std::get<0>(params);

    c.v.mode = SORT;

    if (c.v.size() > c.size_limit)
        throw SizeLimitException(c.v.size(), c.size_limit);

    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>){
        algorithm(std::forward<Args>(args)...);
        std::thread gui_thread([&c](){
            screen_sort<T>(c);
        });
        gui_thread.detach();
    } else {
        auto result = algorithm(std::forward<Args>(args)...);

        std::thread gui_thread([&c](){
            screen_sort<T>(c);
        });
        gui_thread.detach();

        return result;
    }
}