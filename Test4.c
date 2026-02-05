#include "raylib.h"
#include <stdio.h>

int main()
{
    const int ScreenWidth = 600;
    const int ScreenHeight = 300;
    
    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;
    
    InitWindow(ScreenWidth, ScreenHeight, "Test4-Logo");
    
    const Color Gold = {255, 203, 0, 100};
    
    Font Zapfino = LoadFontEx("C:\\Users\\admin\\Desktop\\RayLib Project's\\Zapfino.ttf", 125, 0, 0);
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(MAROON);
            // DrawRectangle(central_x - 200,central_y - 150, 400, 200, MAROON);
            DrawTextEx(Zapfino,"TOPKING", (Vector2){central_x - 200, central_y - 55} ,  (float)Zapfino.baseSize, 8, BLACK);
            DrawRectangle(central_x + 32, central_y - 44, 10, 10, Gold);
            DrawRectangle(central_x + 28, central_y - 48, 10, 10, Gold);
            
            
            // TODO:FIND OR MAKE A SIMPLE LOGO DISIGN FOR THIS TEST.
            //IMPLEMENT FIRE STYLE RECTANGE ABOVE "I" FOR THE REPLACEMENT OF THIS "." (Have Fun).
            //TODO2:MAKE THE MAROON RECTANGE THE BACKGROUND AND SET IT accordingly.
            // DrawRectangle()      //Currently Working...

        EndDrawing();
    }
    
    UnloadFont(Zapfino);
    CloseWindow();
    return 0;
    
    //PS NOTE:There is a take away to take if you create any object and define it size in raylib it's start expanding from there (like's it's pivot point is (0,0) from there), so..
    //Example: the screen width is 800 / 2 = 400 / 2 = 200 (it's offset's it to centre) btw same for screen height too. :)
    //And To Centre The Text You Divide it by One More time So they Offset is at the center of rectangle (If it's Not Exactly The Value then Please See For Other Factor's).
}