#include "raylib.h"
#include <stdio.h>

int main()
{
    //Initialization
    const int ScreenWidth = 600;
    const int ScreenHeight = 600;
    
    int central_x = ScreenWidth/2;
    int central_y = ScreenHeight/2;
    
    // Camera2D camera = { 0 };
    
    InitWindow(ScreenWidth, ScreenHeight, "Test3-Basic Movements"); 
    
    Vector2 CirclePosition = {central_x,central_y};
    
    const float speed = 4.0f;
    
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        //Keyboard Controls
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            CirclePosition.x += speed;
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            CirclePosition.x -= speed;
        if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            CirclePosition.y -= speed;
        if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            CirclePosition.y += speed;
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // DrawLine()
            // DrawText("Move Bal")
            DrawCircleV(CirclePosition, 30, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}