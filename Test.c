#include "raylib.h"
#include <stdio.h>

int main()
{
    //Initialization
    const int ScreenWidth = 600;
    const int ScreenHeight = 600;
    //Centering the x and y 
    const int x = ScreenWidth/2;
    const int y = ScreenHeight/2;
    
    const int TextOffset_X = -150;
    const int TextOffset_Y = -50;

    printf("x: %d\n",x+TextOffset_X);
    printf("y: %d\n",y+TextOffset_Y);

    InitWindow(ScreenWidth, ScreenHeight, "Testing");

    SetTargetFPS(60);
    // ToggleFullscreen();

    //Main Game Loop
    while(!WindowShouldClose())
    {
        //Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Finally, The Raylib is Working!!",x + TextOffset_X,y + TextOffset_Y,20,GRAY);
        EndDrawing();
    }
    //DeInitialization
    CloseWindow();
    return 0;
}