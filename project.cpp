#include "raylib.h"
#include<cstdlib>
#include<cstring>
#include<string>
#include<raymath.h>
using namespace std;
int screenwidth = 800;
int screenheight = 600;
void DisplayStack(int[]);
void TakeInput(int[],char[]);
void DisplayTree(int[]);
void DisplayQueue(int[]);
typedef struct{
    float lifetime;
}Timer;
void Start(Timer * timer,float a)
{
    timer->lifetime = a;
}
void Update(Timer * timer)
{
    if(timer != NULL)
    timer->lifetime -= GetFrameTime();
}
bool Expired(Timer * timer)
{
    if(timer != NULL)
      return timer->lifetime <= 0;
    return 0;
}
void load_managing_window(void)
{
    InitWindow(1000,1000,"Managing");
    SetTargetFPS(60);
    int array[10] = {0};
    char ch[100];
    bool once = 0;
    while(!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
        DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
        if(!once)
        {
            EndDrawing();
            CloseWindow();
            TakeInput(array,ch);
            InitWindow(1000,1000,"Managing");
            BeginDrawing();
            DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
            DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
            once = true;
        }
        DrawText("Values You Entered: ",20,121,20,RAYWHITE);
        DrawText(ch,MeasureText("Values You Entered: ",20)+30,121,20,RAYWHITE);
        DrawText(
        "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n\nEnter 1,2 or 3: ",20,181,20,RAYWHITE);
        if(IsKeyPressed(KEY_ONE))
        {
            EndDrawing();
            CloseWindow();
            DisplayStack(array);
            InitWindow(1000,1000,"Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
            DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
            DrawText("Values You Entered: ",20,121,20,RAYWHITE);
            DrawText(ch,MeasureText("Values You Entered: ",20)+30,121,20,RAYWHITE);
            DrawText(
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n\nEnter 1,2 or 3: ",20,181,20,RAYWHITE);
        }
        else if(IsKeyPressed(KEY_TWO))
        {
            EndDrawing();
            CloseWindow();
            DisplayQueue(array);
            InitWindow(1000,1000,"Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
            DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
            DrawText("Values You Entered: ",20,121,20,RAYWHITE);
            DrawText(ch,MeasureText("Values You Entered: ",20)+30,121,20,RAYWHITE);
            DrawText(
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n\nEnter 1,2 or 3: ",20,181,20,RAYWHITE);
        }
        else if(IsKeyPressed(KEY_THREE))
        {
            EndDrawing();
            CloseWindow();
            DisplayTree(array);
            InitWindow(1000,1000,"Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
            DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
            DrawText("Values You Entered: ",20,121,20,RAYWHITE);
            DrawText(ch,MeasureText("Values You Entered: ",20)+30,121,20,RAYWHITE);
            DrawText(
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n\nEnter 1,2 or 3: ",20,181,20,RAYWHITE);
        } 
        EndDrawing();
    }
    CloseWindow();
}
void DisplayQueue(int array[])
{
    const int screenheight = 600;
    const int screenwidth = 1000;
    InitWindow(screenwidth,screenheight,"Queues");
    int i=0,j=0;
    while(!WindowShouldClose() && i < 10)
    {
        BeginDrawing();
        DrawText("Elements are inserted in the queue in to following order",10,10,20,RAYWHITE);
        DrawRectangle(10+j,300,80,50,RAYWHITE);
        DrawText(TextFormat("%i",array[i]),10+j+40,325,30,BLACK);
        if(IsKeyPressed(KEY_SPACE))
        {     
            j += 90;
            ++i;
        }
        EndDrawing(); 
    }
    ClearBackground(BLACK);
    bool flag = false;
    j=i=0;
    int l = 0;
    while(!WindowShouldClose() && l < 10)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press p to Dequeue an element",10,10,20,RAYWHITE);
        while(i<10)
        {
            DrawRectangle(10+j,300,80,50,GREEN);
            DrawText(TextFormat("%i",array[i]),10+j+40,325,30,BLACK);
            j += 90;
            ++i;
        }
        if(IsKeyPressed(KEY_P))
        {
            ++l;
            flag = true;
        }
        if(flag)
        {
            DrawText(TextFormat("Element Dequeued: %i",array[l-1]),10,35,20,RAYWHITE);
            DrawText("Remaining Queue: ",10,160,20,RAYWHITE);
        }
        i=l;
        j = 90*l;
        EndDrawing();
    }
    CloseWindow();
        
}
void DisplayTree(int array[]){}
void TakeInput(int array[],char str[])
{
    InitWindow(1000,1000,"Managing");
    ClearBackground(BLACK);
    
    int i=0;
    int j=0;
    while(!WindowShouldClose() && i<10)
    {
        BeginDrawing();
        DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
        DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
        if(IsKeyPressed(KEY_SPACE))
        {
            ++i;
            str[j++] = ' ';
        }
        if(IsKeyPressed(KEY_ZERO))
        {
            array[i] *= 10;
            str[j] = '0';
            ++j;
        } 
        if(IsKeyPressed(KEY_ONE))
        {
            array[i] *= 10;
            array[i] += 1;
            str[j] = '1';
            ++j;
        }  
        if(IsKeyPressed(KEY_TWO))
        {
            array[i] *= 10;
            array[i] += 2;
            str[j] = '2';
            ++j;
        }  
        if(IsKeyPressed(KEY_THREE))
        {
            array[i] *= 10;
            array[i] += 3;
            str[j] = '3';
            ++j;
        }  
        if(IsKeyPressed(KEY_FOUR))
        {
            array[i] *= 10;
            array[i] += 4;
            str[j] = '4';
            ++j;
        }  
        if(IsKeyPressed(KEY_FIVE))
        {
            array[i] *= 10;
            array[i] += 5;
            str[j] = '5';
            ++j;
        }  
        if(IsKeyPressed(KEY_SIX))
        {
            array[i] *= 10;
            array[i] += 6;
            str[j] = '6';
            ++j;
        }  
        if(IsKeyPressed(KEY_SEVEN))
        {
            array[i] *= 10;
            array[i] += 7;
            str[j] = '7';
            ++j;
        }  
        if(IsKeyPressed(KEY_EIGHT))
        {
            array[i] *= 10;
            array[i] += 8;
            str[j] = '8';
            ++j;
        }  
        if(IsKeyPressed(KEY_NINE))
        {
            array[i] *= 10;
            array[i] += 9;
            str[j] = '9';
            ++j;
        }  
        DrawText(str,MeasureText("Input 10 random values to store: ",20)+20,100,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    
}
void DisplayStack(int array[])
{
    SetTargetFPS(144);
    //DrawFPS(0,0);
    const int screenheight = 600;
    const int screenwidth = 1000;
    InitWindow(screenwidth,screenheight,"Stacks");
    int j=30;
    int i=0; 
    Texture2D top = LoadTexture("resources/top.png");
    Vector2 pos = {200-(float)top.width,540};
    while(!WindowShouldClose() && i < 10)
    {
        BeginDrawing();
        //ClearBackground(BLACK);
        DrawText("Elements are pushed in the following order",10,10,20,RAYWHITE);
        
        DrawRectangle(200,600-j,250,30,RAYWHITE);
        DrawText(TextFormat("%i",array[i]),280,600-j+4,30,BLACK);
        //DrawTextureV(top,pos,RAYWHITE);
        if(IsKeyPressed(KEY_SPACE))
        {     
            j += 35;
            pos.y -= 35.0f;
            ++i;
        }
        EndDrawing(); 
    }
    i = 0;
    j = 30;
    pos.y = 570.0f;
    int l = 10;
    bool flag = false;
    ClearBackground(BLACK);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press p to pop an element",10,10,20,RAYWHITE);
        while(i<l)
        {
            DrawRectangle(200,600-j,250,30,GREEN);
            DrawText(TextFormat("%i",array[i]),280,600-j+4,30,BLACK);
            j += 35;
            pos.y -= 35.0f;
            ++i;
        }
        if(IsKeyPressed(KEY_P))
        {
            --l;
            flag = true;
        }
        if(flag)
        {
            DrawText(TextFormat("Element Popped: %i",array[i]),10,35,20,RAYWHITE);
            DrawText("Remaining Stack: ",10,160,20,RAYWHITE);
        }
        i=0;
        DrawTextureV(top,pos,RAYWHITE);
        pos.y = 570.0f;
        j = 30;
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
        DrawText("Muhammad Humza (21k-3293)",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-20,20,RAYWHITE);
        DrawText("Yaazir Mehdi (21k-3460)",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-40,20,RAYWHITE);
        DrawText("Bilal Hassan (21k-4669)",screenwidth-MeasureText("Muhammad Humza (21k-XXXX)",20)-10,screenheight-60,20,RAYWHITE);
        DrawText("Click on anyone of the following options:",10.0f,70.0f,20,RAYWHITE);
        DrawText("Made By:",screenwidth-MeasureText("Muhammad Humza (21k-3293)",20)-10,screenheight-80,20,RAYWHITE);
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
