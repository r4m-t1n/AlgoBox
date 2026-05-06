#pragma once

#include <unordered_set>
#include "raylib.h"
#include "rlgl.h"
#include "algobox.hpp"

inline size_t get_monitor_width(){
    return static_cast<size_t>(GetMonitorWidth(GetCurrentMonitor()));
}
inline size_t get_monitor_height() {
    return static_cast<size_t>(GetMonitorHeight(GetCurrentMonitor()));
}

inline void draw_arrows(const float posX, const float posY,
    const float rectangle_width, Color rectangle_color){
    float base_y = posY - 45.0f;
    float bisector_x = posX + ((rectangle_width - 1.0f)/2);
    float bisector_y = posY - 20.0f;
    Vector2 left_top = {posX, base_y};
    Vector2 middle_bot = {bisector_x, bisector_y};
    Vector2 right_top = {posX + rectangle_width - 1.0f, base_y};
    DrawTriangle(
        left_top,
        middle_bot,
        right_top,
        rectangle_color
    );
    DrawLineEx(
        (Vector2) {bisector_x, base_y},
        (Vector2){bisector_x, base_y-20.0f},
        (rectangle_width - 1.0f)/4,
        BLACK
    );
}

template <typename T>
inline std::unordered_set<T> highlighted_indexes(algobox::core<T>& c){
    std::unordered_set<T> highlights;
    for (auto& [key, val]: c.vars.data){
        size_t idx = val.front();
        val.pop();
        if (idx != c.empty_element)
            highlights.insert(idx);
    }
    return highlights;
}