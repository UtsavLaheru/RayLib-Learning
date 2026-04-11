#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main()
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;
    
    //Virtual Screen Width and height
    const int VirtualWidth = 400;
    const int VirtualHeight = 300;
    
    int ChangeableWidth = VirtualWidth;
    bool Changed = true;
    
    float virtualRatio;
    

    
    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;
    
    InitWindow(ScreenWidth, ScreenHeight, "Test8-Pixelized Widget 2");
    
    Vector2 offset = {-200, -100};
    
    Camera2D ScreenSpaceCamera = { 0 };
    ScreenSpaceCamera.zoom = 1.0f;
    
    Camera2D WorldSpaceCamera = { offset };
    WorldSpaceCamera.zoom = 1.0f;
    
    Rectangle box1 = { central_x, central_y, 45, 80};
    Rectangle box2 = { central_x - 70, central_y, 60,30};
    Rectangle box3 = { central_x, central_y - 60, 50, 50};
    
    //origins
    Vector2 box1_origin = { box1.width/central_x, box1.height/central_y};
    Vector2 box2_origin = { box2.width/central_x, box2.height/central_y};
    Vector2 box3_origin = { box3.width/central_x, box3.height/central_y};
    
    RenderTexture2D target;
    
    Vector2 origin = { 0 , 0 };    //Raylib's Origins
    
    float rotation = 0.0f;
    float speed = 60.0f;
    
    float CameraX = 0.0f;
    float CameraY = 0.0f;
    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        //So the ChangeableWidth does not go in Negative value and Cause issue with virtualRatio
        if(ChangeableWidth >= 5)
        {
            if(IsKeyDown(KEY_W))
            {
                ChangeableWidth += 1;
                Changed = true; 
            }
            if(IsKeyDown(KEY_S))
            {
                ChangeableWidth -= 1;
                Changed = true;
            }            
        }
        
        if(Changed)
        {
            virtualRatio = (float)ScreenWidth/(float)ChangeableWidth;
            target = LoadRenderTexture(ChangeableWidth, VirtualHeight);
            Changed = false;
        }
        
        Rectangle sourceRec = { 0.0f , 0.0f, (float)target.texture.width, -(float)target.texture.height};
        Rectangle destRec = { -virtualRatio, -virtualRatio, ScreenWidth + (virtualRatio*2), ScreenHeight + (virtualRatio*2)};
        rotation += GetFrameTime() * speed;
        
        //For Wavey Effect
        CameraX = (sinf((float)GetTime())*50.0f) - 10.0f;
        CameraY = cosf((float)GetTime())*30.0f;
        
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
            DrawFPS(5, 0);
        EndDrawing();
    }
    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}

//NOTE:This Todo list task are not Memory Efficent, (So please don't use it in Raylib like this instead use Camera2D For dynamic approch) :)
//TODO:
//  Make a width slider changer for a 3d effect (fun).   (x)
//  Make it dynamic like we can pixelize at any point (x4 (current), x5, x6...) and the object will be in the center.

//FUNFACT:
//  width slider changer for a 3d effect is Fun But, It's not memory efficent because it spams INFO on the console.