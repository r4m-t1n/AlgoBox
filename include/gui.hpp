#pragma once

#include <thread>
#include <chrono>
#include "raylib.h"
#include "rlgl.h"
#include "algobox.hpp"

void draw_arrows(const float posX, const float posY,
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
bool draw_rectangles(const algobox::core<T>& c,
    const float screen_height, const float rectangle_width,
    const T target, const size_t current_idx, const T maximum){
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
        } else{
            rectangle_color = BLUE;
        }

        DrawRectangleRec(rec, rectangle_color);
    }
    return target_reached;
}

template <typename T>
void screen_search(algobox::core<T>& c, const T target){
    const float screen_height = 720.0f;
    const float screen_width = 720.0f;

    const float rectangle_width = screen_width / c.v.size();

    InitWindow(screen_width, screen_height, "Search Algorithm");
    SetTargetFPS(60);

    T maximum = c.v.get_max();

    bool target_reached = false;
    while (!WindowShouldClose() && !target_reached){
        if (c.v.nodes.empty()){
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        target_reached = draw_rectangles(
            c, screen_height, rectangle_width, target, c.v.nodes.front(), maximum);
            
        EndDrawing();
        c.v.nodes.pop();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    CloseWindow();

}
