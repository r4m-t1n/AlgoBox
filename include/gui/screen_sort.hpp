#pragma once

#include <thread>
#include <chrono>
#include <unordered_set>
#include "raylib.h"
#include "rlgl.h"
#include "algobox.hpp"

template <typename T>
void draw_rectangles_sort(algobox::core<T>& c,
    const float screen_height, const float rectangle_width,
    const std::vector<T>& data, const size_t current_idx, const T maximum,
    const size_t green_swap, const size_t red_swap){

    std::unordered_set<T> highlights = highlighted_indexes(c);

    for (size_t i=0; i<data.size(); i++){
        float rectangle_height = ((float)data[i]/maximum) * screen_height;

        float posX = (float)i * rectangle_width;
        float posY = screen_height - rectangle_height + (rectangle_height / 5);

        Rectangle rec = {posX, posY, rectangle_width - 1.0f, rectangle_height};

        Color rectangle_color;

        if (i == green_swap){
            rectangle_color = GREEN;
        }
        else if (i == red_swap){
            rectangle_color = RED;
            draw_arrows(posX, posY, rectangle_width, rectangle_color);
        }
        else if (current_idx == i){
            rectangle_color = RED;
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
}

template <typename T>
void screen_sort(algobox::core<T>& c){

    const float rectangle_width = c.screen_width / c.v.size();

    InitWindow(c.screen_width, c.screen_height, "Sort Algorithm");
    SetTargetFPS(60);

    T maximum = c.v.get_max();

    while (!WindowShouldClose()){
        if (c.v.copies.empty()){
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        algobox::State<T> frame = c.v.copies.front();

        draw_rectangles_sort(
            c, c.screen_height, rectangle_width,
            frame.data, frame.index, maximum,
            frame.swap_1, frame.swap_2);

        EndDrawing();
        c.v.copies.pop();

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(c.time * 1000.0f)));
    }

    CloseWindow();

}