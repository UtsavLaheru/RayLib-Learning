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
    Rectangle box3 = { central_x, central_y - 60, 50, 50}
    
    Vector2 origin = { 0 , 0 };    //Raylib's Origins
    
    float rotation = 0.0f;
    float speed = 60.0f;
    
    float CameraX = 0.0f;
    float CameraY = 0.0f;
    
    setTargetFPS(60);
    while(!WindowShouldClose)
    {
        if(IsKeyDown(Key_W))
            ChangeableWidth += 1;
        
        float VirtualRatio = (float)ScreenWidth/(float)ChangeableWidth;
        RenderTexture2D target = LoadRenderTexture(VirtualWidth, ChangeableWidth);
        
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
        EndDrawing();
    }
    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}