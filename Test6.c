#include "raylib.h"
#include <stdio.h>

int main()
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;

    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;

    InitWindow(ScreenWidth, ScreenHeight, "Test6-Collision's");
    
    Rectangle Player = {central_x,central_y, 50, 50};
    Rectangle MovingBox = {central_x - 130,central_y - 200, 100, 50};
    int Speed = 2;
    
    float PlayerSpeed = 4.0f;
    
    Rectangle CollisionBoxArea = {0};
    
    bool pause = false;
    bool collision = false;
    
    bool change_control = false;
    // Color CombinedPurple = {95, 58, 114, 255};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        if (!pause) MovingBox.x += Speed;
        
        if ((MovingBox.x + MovingBox.width) >= ScreenWidth || MovingBox.x <= 0) Speed *= -1;
        
        if(IsKeyPressed(KEY_SPACE)) pause = !pause;                            // it works like a toggle switch if pause is true then Not opertor invert's it to false, Vise versa.
        
        if (IsKeyPressed(KEY_TAB)) change_control = !change_control;
        
        
        if (!change_control)
        {
            //we subtract our box (or Player) width and height and divde by 2 To Center the Mouse Pointer.
            Player.x = GetMouseX() - Player.width/2;                                
            Player.y = GetMouseY() - Player.height/2;            
        }
        else
        {
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
                Player.x += PlayerSpeed;
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
                Player.x -= PlayerSpeed;
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
                Player.y -= PlayerSpeed;
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
                Player.y += PlayerSpeed;
        }
        //Clamping the Player to the Screen
        if ((Player.x + Player.width) >= ScreenWidth) Player.x = ScreenWidth - Player.width;
        else if (Player.x <= 0) Player.x = 0;
        
        if ((Player.y + Player.height) >= ScreenHeight) Player.y = ScreenHeight - Player.height;
        else if (Player.y <= 0) Player.y = 0;
        
        
        collision = CheckCollisionRecs(Player, MovingBox);
        
        if (collision)
        {
            CollisionBoxArea = GetCollisionRec(Player, MovingBox);
            
            //X Axis Collision
            if (CollisionBoxArea.x >= (Player.x - Player.width) && Player.y <= MovingBox.y+45 && Player.y >= MovingBox.y-45)
                Player.x = MovingBox.x + Player.width * 2;
            if (CollisionBoxArea.x <= (Player.x - Player.width) && Player.y <= MovingBox.y+45 && Player.y >= MovingBox.y-45)
                Player.x = MovingBox.x - Player.width;
            
            //Y Axis Collision
            if (CollisionBoxArea.y <= Player.y && Player.y >= MovingBox.y+45)
                Player.y = MovingBox.y + Player.height;                                     //Change the Number to an Variable (For Flexibility)
            else if (CollisionBoxArea.y >= Player.y && Player.y <= MovingBox.y-45)
                Player.y = MovingBox.y - Player.height;
        }
        
        // printf("x: %f, %f y: %f, %f\n", CollisionBoxArea.x, Player.x, CollisionBoxArea.y, Player.y);
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(MovingBox, DARKBLUE);
            DrawRectangleRec(Player, MAROON);
            if (collision)
            {
                DrawRectangleRec(CollisionBoxArea, DARKPURPLE);
                DrawText(TextFormat("Collision Area: %d", (int)CollisionBoxArea.width * (int)CollisionBoxArea.height), central_x - 100, central_y + 200, 20, BLACK);
            }
            
            DrawText("Press SPACE to PAUSE/RESUME The MovingBox", 20, central_y + 250,20, LIGHTGRAY);
            
            DrawFPS(10,10);             //Printing or Drawing FPS At A Certain Position.
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
    //Learned:-
    //When We Clamp or Do ScreenWidth - Player.width it means that we set the position of the so, it doesn't go over or under the screen
    //(ex: Player.x = ScreenWidth - Player.width = 750), And 750 is the position of Player in x axis). :)
    //(optional) Player Collide with MovingBox and Stops (Like The player Hit a wall).
    //Done. In order to make a wall like box just use player (x or y) position and compare it with CollisionBoxArea (x or y) and if a axis not being set-up perfectly just use 
    //There Axis and filter out the Collision for that specific axis like in this ex: 45 + MovingBox.y - 45 for checking the Y axis and seting up none interfrence from any sides. 
    //It's Not The Most Practical Way to Do Collision Resolution But It's My Way :)