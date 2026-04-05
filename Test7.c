#include "raylib.h"
#include <stdio.h>
#include <math.h>    //required for sin(), cosf()

int main()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);    //for Minimized Borderless Window
    
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;
    
    //Virtual Screen Width and height
    const int VirtualWidth = 400;
    const int VirtualHeight = 300;
    
    const float virtualRatio = (float)ScreenWidth/(float)VirtualWidth;
    
    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;
    
    InitWindow(ScreenWidth, ScreenHeight, "Test7-Pixelized Widget");
    
    //for testing Only.
    Vector2 offset = {-200 , -100};
    // Camera2D testSpaceCamera = { offset };
    // testSpaceCamera.zoom = 1.5f;
    
    Camera2D ScreenSpaceCamera = { 0 };
    ScreenSpaceCamera.zoom = 1.0f;
    
    Camera2D WorldSpaceCamera = { offset };
    WorldSpaceCamera.zoom = 1.0f;
    
    Rectangle box1 = { central_x, central_y, 45, 80};
    Rectangle box2 = { central_x - 70, central_y, 60, 30};
    Rectangle box3 = { central_x, central_y - 60, 50, 50};
    
    Vector2 box1_origin = { box1.width/central_x, box1.height/central_y};
    Vector2 box2_origin = { box2.width/central_x, box2.height/central_y};
    Vector2 box3_origin = { box3.width/central_x, box3.height/central_y};
    
    //Load all render object in this texture
    RenderTexture2D target = LoadRenderTexture(VirtualWidth, VirtualHeight);
    // printf("width:%f, height:%f\n", box1_origin.x, box1_origin.y);   //origin info 
    
    // Vector2 central_origin = { central_x/2, central_y/2 };
    Vector2 origin = { 0 , 0 };    //Raylib's Origins
    
    float rotation = 0.0f;
    float speed = 60.0f;
    
    float CameraX = 0.0f;
    float CameraY = 0.0f;
    
    //PS:Change it to (Flexible) Variable then hard coded nums 
    Rectangle sourceRec = { 0.0f , 0.0f, (float)target.texture.width, -(float)target.texture.height};
    Rectangle destRec = { -virtualRatio, -virtualRatio, ScreenWidth + (virtualRatio*2), ScreenHeight + (virtualRatio*2)};
    
    // printf("destRec Width:%f, Height:%f\n", ScreenWidth + (virtualRatio*2), ScreenHeight + (virtualRatio*2));
    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        rotation += GetFrameTime() * speed;
        
        //For Wavey Effect
        CameraX = (sinf((float)GetTime())*50.0f) - 10.0f;
        CameraY = cosf((float)GetTime())*30.0f;
        
        // printf("CameraX:%f, CameraY:%f\n", CameraX, CameraY); 
        
        //set the camera's
        ScreenSpaceCamera.target = (Vector2){CameraX, CameraY};
        
        //Rounding WorldSpaceCamera and keeping decimal of ScreenSpace coordinates
        WorldSpaceCamera.target.x = truncf(ScreenSpaceCamera.target.x);
        ScreenSpaceCamera.target.x -= WorldSpaceCamera.target.x;
        ScreenSpaceCamera.target.x *= virtualRatio;
        
        WorldSpaceCamera.target.y = truncf(ScreenSpaceCamera.target.y);
        ScreenSpaceCamera.target.y -= WorldSpaceCamera.target.y;
        ScreenSpaceCamera.target.y *= virtualRatio;
        
        // printf("x:%f, y:%f\n",ScreenSpaceCamera.target.x, WorldSpaceCamera.target.x);
        
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            
            BeginMode2D(WorldSpaceCamera);
                DrawRectanglePro(box1, box1_origin, rotation, MAROON);
                DrawRectanglePro(box2, box2_origin, rotation, BLACK);
                DrawRectanglePro(box3, box3_origin, rotation, DARKBLUE);
            EndMode2D();
        EndTextureMode();
        //Learn  More :)
        
        BeginDrawing();
            ClearBackground(RED);
            BeginMode2D(ScreenSpaceCamera);
                DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
            EndMode2D();
        EndDrawing();
    }
    UnloadRenderTexture(target);
    CloseWindow();
    return 0; 
}


//TODO (Have Fun):
//  Make a width slider changer for a 3d effect (fun).
//  Make it dynamic like we can pixelize at any point (x4 (current), x5, x6...) and the object will be in the center.
//  Understand and Implement texture.                           (x)
//  Understand and Add Camera2D for WorldSpace and ScreenSpace. (x)
//  Learn More about Math.h and learn some code :)              (x)

//FUNFACTS: 
// turncf (for float), turncl (for long), turnc (for double) is used to removes the values after decimal point (e.g. 45.2546554 to 45.0000000).
// By Calling target.texture it mean we are calling the texture attribute in the RenderTexture Type Texture (Texture texture) in raylib.
// In DrawRectanglePro the origin vector isused for decading the origin of rotation (or anchor of shape '+'). 
// Dividing with central or origin for the Rectangle To Positioned to be accurate (meaning height/2 or width (since raylib origin is 0) and for central point x,y using 
// width/central_x or y) makes the position of the rectangle Same as before like we setted it for normally (or when using with DrawRectangleRec).

