#pragma once

#include <unordered_set>
#include <chrono>
#include "raylib.h"
#include "rlgl.h"
#include "algobox.hpp"

template <typename T>
bool draw_rectangles_search(algobox::core<T>& c,
    const float screen_height, const float rectangle_width,
    const T target, const size_t current_idx, const T maximum){

    std::unordered_set<T> highlights = highlighted_indexes(c);

    bool target_reached = false;
    for (size_t i=0; i<c.v.size(); i++){
        float rectangle_height = ((float)c.v.at(i)/maximum) * screen_height;

        float posX = (float)i * rectangle_width;
        float posY = screen_height - rectangle_height + (rectangle_height / 5);

        Rectangle rec = {posX, posY, rectangle_width - 1.0f, rectangle_height};

        Color rectangle_color;

        if (current_idx == i){
            if (c.v.at(current_idx) == target){
                rectangle_color = GREEN;
                DrawRectangleRec(rec, rectangle_color);
                target_reached = true;
            }
            else{
                rectangle_color = RED;
            }
            draw_arrows(posX, posY, rectangle_width, rectangle_color);
        }
        else if (highlights.find(i) != highlights.end()){
            rectangle_color = YELLOW;
        }
        else{
            rectangle_color = BLUE;
        }

        DrawRectangleRec(rec, rectangle_color);
    }
    return target_reached;
}



template <typename T>
void screen_search(algobox::core<T>& c, const T target){

    const float rectangle_width = c.screen_width / c.v.size();

    InitWindow(c.screen_width, c.screen_height, "Search Algorithm");
    SetTargetFPS(60);

    T maximum = c.v.get_max();

    bool target_reached = false;
    while (!WindowShouldClose() && !target_reached){
        if (c.v.nodes.empty()){
            break;
        } else if (c.v.nodes.front() == c.empty_element){
            c.v.nodes.pop();
            continue;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        target_reached = draw_rectangles_search(
            c, c.screen_height, rectangle_width, target, c.v.nodes.front(), maximum);

        EndDrawing();
        c.v.nodes.pop();

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(c.time * 1000.0f)));
    }

    CloseWindow();

}
