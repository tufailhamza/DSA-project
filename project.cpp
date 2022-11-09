#include "raylib.h"
int screenwidth = 800;
int screenheight = 600;
void load_managing_window(void)
{
    InitWindow(1000,1000,"Managing");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("MANAGING WINDOW",100,100,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
void load_searching_window(void)
{
    InitWindow(1000,1000,"Searching");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("SEARCHING WINDOW",100,100,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
void load_sorting_window(void)
{
    InitWindow(1000,1000,"Sorting");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("SORTING WINDOW",100,100,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
int main(void)
{
    int choice;
    InitWindow(screenwidth,screenheight,"Data Structures Project");
    SetTargetFPS(60);
    Texture2D logo = LoadTexture("resources/FAST_logo-removebg-preview.png");
    float logo_width = logo.width/2.5f;
    float logo_height = logo.height;
    float text_width = 50.0f;
    float text_height = 120.0f;
    Rectangle SourceRec = {0.0f,0.0f,logo_width-20,logo_height};
    Rectangle managing = {text_width,text_height,(float)MeasureText("Managing Data Structures",30),40};
    Rectangle searching = {text_width,text_height+50,(float)MeasureText("Searching",30),40};
    Rectangle sorting = {text_width,text_height+100,(float)MeasureText("Sorting",30),40};
    float rotation = 0;
    while(!WindowShouldClose())
    {
        rotation+=0.1f;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(logo,SourceRec,Vector2{screenwidth-logo_width+20,0},RAYWHITE);
        DrawText("Searching, Sorting & Managing Data Structures.",150,10,20,RAYWHITE);
        DrawText("Muhammad Humza (21k-XXXX)",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-20,20,RAYWHITE);
        DrawText("Yaazir Mehdi (21k-3460)",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-40,20,RAYWHITE);
        DrawText("Bilal Hassan (21k-4669)",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-60,20,RAYWHITE);
        DrawText("Click on anyone of the following options:",10.0f,70.0f,20,RAYWHITE);
        DrawText("Made By:",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-80,20,RAYWHITE);
        DrawRectangleRec(managing,BLACK);
        DrawRectangleRec(searching,BLACK);
        DrawRectangleRec(sorting,BLACK);
        DrawText("Managing Data Structures",52.0f,121.0f,20,RAYWHITE);
        DrawText("Searching",text_width,text_height+50+1,20,RAYWHITE);
        DrawText("Sorting",text_width,text_height+100+1,20,RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int x = GetMouseX();
            int y = GetMouseY();
            if(x >= 50)
            {         
                if(y >= managing.y && y < searching.y)
                    choice = 1;
                if(y >= sorting.y && y <= sorting.y+50)
                    choice = 2;
                if(y >= searching.y && y <= searching.y+50)
                    choice = 3;
                break;
            }
                
        }
        EndDrawing();
    }
    screenwidth = screenheight = 1000;
    CloseWindow();
    if(choice == 1)
        load_managing_window();
    else if(choice == 2)
        load_sorting_window();
    else
        load_searching_window();
}
