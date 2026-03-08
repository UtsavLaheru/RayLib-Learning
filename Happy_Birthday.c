#include "raylib.h"
#include <stdio.h>

int main()
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 400;

    const int central_x = ScreenWidth/2;
    const int central_y = ScreenHeight/2;

    InitWindow(ScreenWidth, ScreenHeight, "Test5-Logo Animation");

    const Color Gold = {255, 203, 0, 255};

    Font Zapfino = LoadFontEx("C:\\Users\\admin\\Desktop\\RayLib Project's\\Zapfino.ttf", 90, 0, 0);

    int state = 0;
    float alpha = 0.0f;

    int framesCounter = 0;

    int LowerRectangleMove = 0;
    int UpperRectangleMove = 0;

    int LowerRectangleScale = 0;
    //int UpperRectangleScale = 0; (it breaks the illusion)

    int Loaded = 0;           //For this example it work's like a Oscillation (or frameCounter), but in game it check if the NextScene is loaded.


    SetTargetFPS(60);
    while(!WindowShouldClose()){
        if (state == 0)
        {
            framesCounter++;
            if (framesCounter/20)
            {
                if (alpha < 1.0f)
                    alpha = alpha + 0.01f;
                else
                {
                    framesCounter = 0;
                    state = 1;
                }
            }
        }
        else if (state == 1)
        {
            framesCounter++;
            if (framesCounter/10)
            {
                if (LowerRectangleMove <= 2)
                {
                    LowerRectangleMove += 1;
                    LowerRectangleScale -= 1;
                }
                else if (UpperRectangleMove <= 2)
                    UpperRectangleMove += 1;
                else
                {
                    framesCounter = 0;
                    state = 2;
                }
            }
        }
        else if (state == 2)
            if (LowerRectangleMove >= 0)
            {
                LowerRectangleMove -= 1;
                LowerRectangleScale += 1;
            }
            else if (UpperRectangleMove >= 0)
                UpperRectangleMove -= 1;
            else
            {
                state = 1;
                Loaded++;
                if (Loaded == 20)
                {
                    state = 3;
                }
            }
        else if (state == 3)
        {
            framesCounter++;
            if (framesCounter/12)
                if (alpha > 0.0f)
                    alpha = alpha - 0.01f;
        }


        BeginDrawing();
            ClearBackground(MAROON);
            // DrawRectangle(central_x - 200,central_y - 150, 400, 200, MAROON);
            DrawTextEx(Zapfino,"HAPPY BIRTHDAY TO YOU", (Vector2){central_x - 400, central_y - 40} ,  (float)Zapfino.baseSize, 8, Fade(BLACK, alpha));

            DrawRectangle(central_x - 75 - LowerRectangleMove, central_y - 44 - LowerRectangleMove, 10 + LowerRectangleScale, 10 + LowerRectangleScale, Fade(Gold,  alpha - 0.5));
            DrawRectangle(central_x - 80 + UpperRectangleMove, central_y - 48 + UpperRectangleMove, 10, 10, Fade(Gold, alpha - 0.5));

        EndDrawing();
    }

    UnloadFont(Zapfino);
    CloseWindow();
    return 0;
}

//FUN FACT:If You Use frames Counter / 12 it works as Modules and always output 0 (false) until it reaches 12 (which result in 1 (true)) :)
//ANOTHER FUN FACT:If you don't use "f" when declaring 1.0f or any floating value the compiler treats it as double and can lead to little bit of performance loss due to raylib doing implicit type converstion everytime it's accessed.  (I am using it to adjust it's animation speed).