#pragma once

#include <thread>
#include <chrono>
#include "raylib.h"
#include "rlgl.h"
#include "algobox_vector.hpp"

template <typename T>
void draw_arrows(const algobox::vector<T>& v, const size_t& current_idx){

}

template <typename T>
bool draw_rectangles(const algobox::vector<T>& v,
    const float& screen_height, const float& rectangle_width,
    const T& target, const size_t& current_idx, const T& maximum){
    bool target_reached = false;
    for (size_t i=0; i<v.size(); i++){
        float rectangle_height = ((float)v.at(i)/maximum) * screen_height;

        float posX = (float)i * rectangle_width;
        float posY = screen_height - rectangle_height;

        Rectangle rec = {posX, posY, rectangle_width - 1.0f, rectangle_height};

        Color rectangle_color;

        if (current_idx == i){
            if (v.at(current_idx) == target){
                rectangle_color = GREEN;
                DrawRectangleRec(rec, rectangle_color);
                target_reached = true;
            }
            else{
                rectangle_color = RED;
            }
        } else{
            rectangle_color = BLUE;
        }

        DrawRectangleRec(rec, rectangle_color);
    }
    return target_reached;
}

template <typename T>
void screen_search(algobox::vector<T>& v, T target){
    const float screen_height = 720.0f;
    const float screen_width = 720.0f;

    const float rectangle_width = screen_width / v.size();

    InitWindow(screen_width, screen_height, "Search Algorithm");
    SetTargetFPS(60);

    T maximum = v.get_max();

    bool target_reached = false;
    while (!WindowShouldClose() && !target_reached){
        if (v.nodes.empty()){
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        target_reached = draw_rectangles(
            v, screen_height, rectangle_width, target, v.nodes.front(), maximum);
            
        EndDrawing();
        v.nodes.pop();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    CloseWindow();

}
