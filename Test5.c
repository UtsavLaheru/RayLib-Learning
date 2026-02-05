#include "raylib.h"
#include <stdio.h>

int main()
{
    const int ScreenWidth = 600;
    const int ScreenHeight = 300;
    
    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;
    
    InitWindow(ScreenWidth, ScreenHeight, "Test4-Logo");
    
    const Color Gold = {255, 203, 0, 255};
    
    Font Zapfino = LoadFontEx("C:\\Users\\admin\\Desktop\\RayLib Project's\\Zapfino.ttf", 125, 0, 0);
    
    int state = 0;
    float alpha = 1.0f;
    
    int
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(MAROON);
            // DrawRectangle(central_x - 200,central_y - 150, 400, 200, MAROON);
            DrawTextEx(Zapfino,"TOPKING", (Vector2){central_x - 200, central_y - 55} ,  (float)Zapfino.baseSize, 8, Fade(BLACK, alpha));
            DrawRectangle(central_x + 32, central_y - 44, 10, 10, Fade(Gold,  alpha - 0.5));
            DrawRectangle(central_x + 28, central_y - 48, 10, 10, Fade(Gold, alpha - 0.5));
            
        EndDrawing();
    }
    
    UnloadFont(Zapfino);
    CloseWindow();
    return 0;
}