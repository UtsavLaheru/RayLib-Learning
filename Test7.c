#include "raylib.h"
#include <stdio.h>
#include <math.h>    //required for sin(), cosf()

int main()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;
    
    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;
    
    InitWindow(ScreenWidth, ScreenHeight, "Test7-Pixelized Widget");
    
    Vector2 offset = {-200 , -100};
    
    Camera2D testSpaceCamera = {offset};
    testSpaceCamera.zoom = 1.5f;
    
    Rectangle box1 = { central_x, central_y, 45, 80};
    Rectangle box2 = { central_x - 70, central_y, 60, 30};
    Rectangle box3 = { central_x, central_y - 60, 50, 50};
    
    Vector2 box1_origin = { box1.width/central_x, box1.height/central_y};
    Vector2 box2_origin = { box2.width/central_x, box2.height/central_y};
    Vector2 box3_origin = { box3.width/central_x, box3.height/central_y};
    
    
    // printf("width:%f, height:%f\n", box1_origin.x, box1_origin.y);   //origin info 
    
    // Vector2 central_origin = { central_x/2, central_y/2 };
    // Vector2 origin = { 0 , 0 };    //Raylib's Origins
    
    float rotation = 0.0f;
    
    float speed = 60.0f;
    
    // SetWindowMinSize(ScreenWidth, ScreenHeight);
    // SetWindowMaxSize(ScreenWidth, ScreenHeight);
    
    
    SetTargetFPS(60);
    // ToggleBorderlessWindowed();
    while(!WindowShouldClose())
    {
        rotation += GetFrameTime() * speed;
        BeginDrawing();
            BeginMode2D(testSpaceCamera);
                ClearBackground(RAYWHITE);
                DrawRectanglePro(box1, box1_origin, rotation, MAROON);
                DrawRectanglePro(box2, box2_origin, rotation, BLACK);
                DrawRectanglePro(box3, box3_origin, rotation, DARKBLUE);
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0; 
}

//TODO (Have Fun):
//Understand and Add Camera2D for WorldSpace and ScreenSpace.
//Understand and Implement texture.
//Learn More about Math.h and learn some code :)

//FUNFACTS: 
// In DrawRectanglePro the origin vector isused for decading the origin of rotation (or anchor of shape '+'). 
// Dividing with central or origin for the Rectangle To Positioned to be accurate (meaning height/2 or width (since raylib origin is 0) and for central point x,y using 
// width/central_x or y) makes the position of the rectangle Same as before like we setted it for normally (or when using with DrawRectangleRec).

