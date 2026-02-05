#include "raylib.h"
#include <stdio.h>

int main(){
    //Initialization
    const int ScreenWidth = 600;
    const int ScreenHeight = 600;
    
    // const int Central_x = ScreenWidth/2;
    const int Central_y = ScreenHeight/2;
    
    
    InitWindow(ScreenWidth, ScreenHeight, "Test2-DeltaTime");
    
    Vector2 Circle = {0, Central_y};
    
    const float CircleRadius = 30.0f;
    
    const float speed = 30.0f;
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        Circle.x += GetFrameTime() * speed;
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircleV(Circle,CircleRadius,RED);
            DrawText("Cirlce is Moving Using DeltaTime",10,25,20,GRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}