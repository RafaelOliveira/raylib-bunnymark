/*******************************************************************************************
*
*   BunnyMark - Rafael Oliveira
*   Made with raylib
*
********************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "raylib.h"
#define maxArray 100000

struct Bunny {
    float x;
    float y;
    float speedX;
    float speedY;
};

void AddBunnies();
void Update();
void Render();

int indexArray = -1; 
struct Bunny bunnies[maxArray];

Texture2D bunnyTex;

float gravity = 0.5;
int maxX = 0;
int maxY = 0;
int minX = 0;
int minY = 0;

char fpsMsg[30];

int main()
{    
    const int screenWidth = 800;
    const int screenHeight = 600;
    Color backgroundColor = (Color){ 42, 51, 71, 255 };    
    
    srand(time(0));
    
    InitWindow(screenWidth, screenHeight, "BunnyMark");    
    
    bunnyTex = LoadTexture("wabbit_alpha.png");
    
    maxX = screenWidth - bunnyTex.width;
	maxY = screenHeight - bunnyTex.height;	
    
    SetTargetFPS(60);    

    while (!WindowShouldClose())
    {             
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            AddBunnies();
        
        Update();                

        BeginDrawing();        
        ClearBackground(backgroundColor);
        Render();                  
        EndDrawing();        
    }    
    
    // unload
    UnloadTexture(bunnyTex);
    memset(bunnies, 0, sizeof(bunnies));
    
    CloseWindow();    
    
    return 0;
}

void AddBunnies()
{
    if (indexArray == (maxArray - 1))
        return;
    
    for (int i = 0; i < 1000; i++)
    {
        if ((indexArray + 1) < maxArray)
        {
            struct Bunny bunny;
            bunny.x = 0;
            bunny.y = 0;
            bunny.speedX = rand() % 8;
            bunny.speedY = rand() % 5 - 2.5;
            
            indexArray++;
            bunnies[indexArray] = bunny;
        }
        else
            break;
    }
}

void Update()
{
    for (int i = 0; i < (indexArray + 1); i++) 
    {                
        bunnies[i].x += bunnies[i].speedX;
        bunnies[i].y += bunnies[i].speedY;
        bunnies[i].speedY += gravity;			
        
        if (bunnies[i].x > maxX) 
        {
            bunnies[i].speedX *= -1;
            bunnies[i].x = maxX;
        } 
        else if (bunnies[i].x < minX) 
        {
            bunnies[i].speedX *= -1;
            bunnies[i].x = minX;
        }
        
        if (bunnies[i].y > maxY) 
        {
            bunnies[i].speedY *= -0.8;
            bunnies[i].y = maxY;
            
            if ((rand() % 1) > 0.5)
                bunnies[i].speedY -= 3 + rand() % 4;
        }
        else if (bunnies[i].y < minY) 
        {
            bunnies[i].speedY = 0;
            bunnies[i].y = minY;
        }	
    }
}

void Render()
{
    for (int i = 0; i < (indexArray + 1); i++)    
        DrawTexture(bunnyTex, bunnies[i].x, bunnies[i].y, WHITE); 
    
    sprintf(fpsMsg, "bunnies: %d fps: %.0f", (indexArray + 1), GetFPS());
    DrawText(fpsMsg, 10, 10, 20, WHITE);
}