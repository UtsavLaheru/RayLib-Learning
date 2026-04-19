#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main()
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;
    
    //Virtual Screen Width and height
    const int VirtualWidth = ScreenWidth/2;       //For 2x (Current) the Width is 400 and Height 300
    const int VirtualHeight = ScreenHeight/2;
    
    //For Flexibly Changing Width and Height
    int ChangeableHeight = VirtualHeight;
    int ChangeableWidth = VirtualWidth;
    bool Changed = true;
    
    float virtualRatio;
    
    
    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;
    
    InitWindow(ScreenWidth, ScreenHeight, "Test8-Pixelized Widget 2");
    
 
    
    Camera2D ScreenSpaceCamera = { 0 };
    ScreenSpaceCamera.zoom = 1.0f;
    
    
    
    
    /* printf("Offset X:%f, Y:%f\n", offset_d.x, offset_d.y); */
    
    Camera2D WorldSpaceCamera = { 0 };
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
            if(IsKeyPressed(KEY_R))
            {
                ChangeableWidth = VirtualWidth;
                Changed = true;
            }
            if(IsKeyDown(KEY_DOWN))
            {
                WorldSpaceCamera.zoom -= 0.01f;
                printf("zoom:%f\n", WorldSpaceCamera.zoom);
                Changed = true;
            }
            //3x Pixalization
            if(IsKeyPressed(KEY_TWO))
            {
                ChangeableWidth = ScreenWidth/3;
                ChangeableHeight = ScreenHeight/3;
                WorldSpaceCamera.zoom = 1.0f - 0.4f; 
                Changed = true;
            }
            //4x Pixalization
            if(IsKeyPressed(KEY_THREE))
            {
                ChangeableWidth = ScreenWidth/4;
                ChangeableHeight = ScreenHeight/4;
                WorldSpaceCamera.zoom = 1.0f - 0.5f;
                Changed = true;
            }
            //5x Pixalization
            if(IsKeyPressed(KEY_FOUR))
            {
                ChangeableWidth = ScreenWidth/5;
                ChangeableHeight = ScreenHeight/5;
                WorldSpaceCamera.zoom = 1.0f - 0.6f;
                Changed = true;
            }
            //Learn  More :)
        }
        
        if(Changed)
        {
            Vector2 offset = {-ChangeableWidth, -ChangeableHeight}; 
            //duplicate of offset for testing.
            Vector2 offset_d = { offset.x - (offset.x/2), offset.y - (offset.y/2)};
            WorldSpaceCamera.offset =  offset_d;
            virtualRatio = (float)ScreenWidth/(float)ChangeableWidth;
            target = LoadRenderTexture(ChangeableWidth, ChangeableHeight);
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

//NOTE: This Todo list task are not Memory Efficent, (So please don't use it in Raylib like this instead use Camera2D For dynamic approch) :)

//NOTE2: To implement the zoom Part (1.0f (original zoom) - pixelized zoom (like (3x) 0.2 + 2,(4x) 0.3 + 2,..., or (3x) 0.3 + 1, (4x) 0.4 + 1).

//TODO:
//  Make a width slider changer for a 3d effect (fun).   (x)
//  Make it dynamic like we can pixelize at any point (2x (current), 3x, 4x, 5x, 6x...) and the object will be in the center.

//FUNFACT:
//  width slider changer for a 3d effect is Fun But, It's not memory efficent because it spams INFO on the console.
//  Another Written is The Offset_d or Offset Formula for  { offset.x / (offset.x*2), offset.y / (offset.y*2) } (Have Fun).
//  offset.x + (offset.x*2)/10, offset.y + (offset.y*2)/10.
