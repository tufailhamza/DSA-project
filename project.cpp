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
void DisplayLinkedList(int[]);
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
class CircularQueue{
    public:
    int front,rear,*arr,n;
    CircularQueue(int n)
    {
        front = rear = -1;
        this->n = n;
        arr = (int*)malloc(n*sizeof(arr));
    }
    bool isFull()
    {
        return ((front == 0 && rear == n-1) || (front == rear+1));
    }
    void insert(int val) {
    if ((front == 0 && rear == n-1) || (front == rear+1))
    {
      //cout<<"Queue Overflow \n";
      return;
    }
    if (front == -1) 
    {
      front = 0;
      rear = 0;
    } 
    else 
    {
        if (rear == n - 1)
            rear = 0;
        else
            rear = rear + 1;
    }
    arr[rear] = val ;
    }
    int Delete()
    {
        if (front == -1) 
        {
            return -1;
        }
        int temp = front;
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else 
        {
            if (front == n - 1)
            front = 0;
            else
            front = front + 1;
        }
        return arr[temp];
    }
    void copy(int array[])
    {
        for(int i=0;i<n;++i)
            insert(array[i]);
    }
};
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
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ",20,181,20,RAYWHITE);
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
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ",20,181,20,RAYWHITE);
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
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ",20,181,20,RAYWHITE);
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
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ",20,181,20,RAYWHITE);
        } 
        else if(IsKeyPressed(KEY_FOUR))
        {
            EndDrawing();
            CloseWindow();
            DisplayLinkedList(array);
            InitWindow(1000,1000,"Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures",350,20,30,RAYWHITE);
            DrawText("Input 10 random values to store: ",20,100,20,RAYWHITE);
            DrawText("Values You Entered: ",20,121,20,RAYWHITE);
            DrawText(ch,MeasureText("Values You Entered: ",20)+30,121,20,RAYWHITE);
            DrawText(
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Data in the form of a binary Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ",20,181,20,RAYWHITE);
        } 
        EndDrawing();
    }
    CloseWindow();
}
void DisplayLinkedList(int array[])
{
    const int screenheight = 600;
    const int screenwidth = 1000;
    int i=0,j=0;
    InitWindow(screenwidth,screenheight,"Linked Lists");
    while(!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Select one of the following options\n1)Singly Linked List\n2)Doubly Linked List\n3)Circular linked list\nEnter the format in which you want to store the data: ",10,10,20,RAYWHITE);
        if(IsKeyPressed(KEY_ONE))
        {
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            while(!WindowShouldClose() && i < 10)
            {
                BeginDrawing();
                DrawText("Elements are inserted in the Singly Linked in to following order",10,230,20,RAYWHITE);
                DrawRectangle(10+j+2,300,50,50,RAYWHITE);
                if(i <= 8)
                {
                DrawLine(50+j,325,85+j,325,RAYWHITE);
                DrawLine(70+j,315,85+j,325,RAYWHITE);
                DrawLine(70+j,335,85+j,325,RAYWHITE);
                }
                DrawText(TextFormat("%i",array[i]),20+j,325,25,BLACK);
                if(IsKeyPressed(KEY_SPACE))
                {     
                    j += 70;
                    ++i;
                } 
                EndDrawing();
            }
        }
        if(IsKeyPressed(KEY_TWO))
        {
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            while(!WindowShouldClose() && i < 10)
            {
                BeginDrawing();
                DrawText("Elements are inserted in the Doubly Linked List in to following order",10,230,20,RAYWHITE);
                DrawRectangle(10+j+2,300,50,50,RAYWHITE);
                if(i <= 8)
                {
                DrawLine(50+j,310,85+j,310,RAYWHITE);
                DrawLine(70+j,300,85+j,310,RAYWHITE);
                DrawLine(70+j,320,85+j,310,RAYWHITE);
                
                
                DrawLine(55+j,340,75+j,330,RAYWHITE);
                DrawLine(55+j,340,75+j,350,RAYWHITE);
                DrawLine(50+j,340,90+j,340,RAYWHITE);
                }
                
                DrawText(TextFormat("%i",array[i]),20+j,325,25,BLACK);
                if(IsKeyPressed(KEY_SPACE))
                {     
                    j += 70;
                    ++i;
                } 
                EndDrawing();
            }
        }
        if(IsKeyPressed(KEY_THREE))
        {
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            while(!WindowShouldClose() && i < 10)
            {
                BeginDrawing();
                DrawText("Elements are inserted in the Circular Linked List in to following order",10,230,20,RAYWHITE);
                DrawRectangle(10+j+2,300,50,50,RAYWHITE);
                if(i > 0)
                {
                DrawLine(j-20,325,15+j,325,RAYWHITE);
                DrawLine(j,315,15+j,325,RAYWHITE);
                DrawLine(j,335,15+j,325,RAYWHITE);
                }
                if(i>8)
                {
                    DrawLine(37,350,37,370,RAYWHITE);
                    
                    DrawLine(37,350,17,360,RAYWHITE);
                    DrawLine(37,350,57,360,RAYWHITE);
                    
                    DrawLine(37,370,52+j,370,RAYWHITE);
                    DrawLine(52+j,350,52+j,370,RAYWHITE);
                }     
                DrawText(TextFormat("%i",array[i]),20+j,325,25,BLACK);
                if(IsKeyPressed(KEY_SPACE))
                {     
                    j += 70;
                    ++i;
                } 
                EndDrawing();
            }
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
    Texture2D front = LoadTexture("resources/front.png");
    Texture2D rear = LoadTexture("resources/rear.png");
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
    bool first = true;
    bool checkifenqueued;
    j=i=0;
    int l = 0;
    int front_pos,rear_pos;
    int element;
    CircularQueue q(10);
    q.copy(array);
    while(!WindowShouldClose() && l < 10)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press p to Dequeue an element\n\nEnter an element to Enqueue: ",10,10,20,RAYWHITE);
        front_pos = q.front*90;
        rear_pos = q.rear*90;
        DrawTexture(front,10+front_pos,300+(float)front.width,RAYWHITE);
        DrawTexture(rear,10+rear_pos,300+(float)front.width,RAYWHITE);
        int f = q.front,r = q.rear;
        if(f <= r)
        {
            while(f <= r)
            {
                DrawRectangle(10+f*90,300,80,50,GREEN);
                DrawText(TextFormat("%i",q.arr[f]),50+f*90-30,325,30,BLACK);
                ++f;
            }
        }
        else
        {
            while(f <= q.n-1)
            {
                DrawRectangle(10+f*90,300,80,50,GREEN);
                DrawText(TextFormat("%i",q.arr[f]),50+f*90-30,325,30,BLACK);
                ++f;
            }
            f = 0;
            while(f <= r)
            {
                DrawRectangle(10+f*90,300,80,50,GREEN);
                DrawText(TextFormat("%i",q.arr[f]),50+f*90-30,325,30,BLACK);
                ++f;
            }
        }
        int hehe;
        if(IsKeyPressed(KEY_P))
        {
            flag = true;
            hehe = q.Delete();
            element = 0;
        }
        if(flag)
        {
            DrawText(TextFormat("Element Dequeued: %i",hehe),10,35,20,RAYWHITE);
            DrawText("Remaining Queue: ",10,160,20,RAYWHITE);
        }
        if(q.isFull())
        {
            DrawText("Queue Full!",MeasureText("Enter an element to Enqueue: ",20)+10,70,20,RAYWHITE);
        }
        else
        {
            if(IsKeyPressed(KEY_ZERO))
                element *= 10;
            if(IsKeyPressed(KEY_ONE))
            {
                element *= 10;
                element += 1;
            }
            if(IsKeyPressed(KEY_TWO))
        {
            element *= 10;
            element += 2;

        }  
        if(IsKeyPressed(KEY_THREE))
        {
            element *= 10;
            element += 3;

        }  
        if(IsKeyPressed(KEY_FOUR))
        {
            element *= 10;
            element += 4;
        }  
        if(IsKeyPressed(KEY_FIVE))
        {
            element *= 10;
            element += 5;
        }  
        if(IsKeyPressed(KEY_SIX))
        {
            element *= 10;
            element += 6;
        }  
        if(IsKeyPressed(KEY_SEVEN))
        {
            element *= 10;
            element += 7;
        }  
        if(IsKeyPressed(KEY_EIGHT))
        {
            element *= 10;
            element += 8;
        }  
        if(IsKeyPressed(KEY_NINE))
        {
            element *= 10;
            element += 9;
        }
        DrawText(TextFormat("%i",element),MeasureText("Enter an element to Enqueue: ",20)+10,70,20,RAYWHITE);
        if(IsKeyPressed(KEY_ENTER))
        {
        q.insert(element);
            element = 0;
        }
        }
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
    int temp;
    ClearBackground(BLACK);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press p to pop an element\n\nEnter an element to push into stack: ",10,10,20,RAYWHITE);
        while(i<l)
        {
            DrawRectangle(200,600-j,250,30,GREEN);
            DrawText(TextFormat("%i",array[i]),280,600-j+4,30,BLACK);
            j += 35;
            pos.y -= 35.0f;
            ++i;
        }
        
        if(l == 10)
        {
                DrawText("Stack overflow!",MeasureText("Enter an element to push into stack: ",20)+10,70,20,RAYWHITE);
        }
        else
        {
            if(IsKeyPressed(KEY_ZERO))
            array[l-1] *= 10;  
        if(IsKeyPressed(KEY_ONE))
        {
            array[l] *= 10;
            array[l] += 1;
        }  
        if(IsKeyPressed(KEY_TWO))
        {
            array[l] *= 10;
            array[l] += 2;

        }  
        if(IsKeyPressed(KEY_THREE))
        {
            array[l] *= 10;
            array[l] += 3;

        }  
        if(IsKeyPressed(KEY_FOUR))
        {
            array[l] *= 10;
            array[l] += 4;
        }  
        if(IsKeyPressed(KEY_FIVE))
        {
            array[l] *= 10;
            array[l] += 5;
        }  
        if(IsKeyPressed(KEY_SIX))
        {
            array[l] *= 10;
            array[l] += 6;
        }  
        if(IsKeyPressed(KEY_SEVEN))
        {
            array[l] *= 10;
            array[l] += 7;
        }  
        if(IsKeyPressed(KEY_EIGHT))
        {
            array[l] *= 10;
            array[l] += 8;
        }  
        if(IsKeyPressed(KEY_NINE))
        {
            array[l] *= 10;
            array[l] += 9;
        }
        DrawText(TextFormat("%i",array[l]),MeasureText("Enter an element to push into stack: ",20)+10,70,20,RAYWHITE);
        if(IsKeyPressed(KEY_ENTER))
            ++l;
        }
        if(IsKeyPressed(KEY_P))
        {
            temp = array[l-1];
            array[l-1] = 0;
            --l;
            flag = true;
        }
        if(flag)
        {
            DrawText(TextFormat("Element Popped: %i",temp),10,35,20,RAYWHITE);
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
