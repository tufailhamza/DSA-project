#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include<math.h>
#include<string.h>
using namespace std;
int X=370,Y=20;
int i=0;
class Node
{
   public:
    int Id;
    char Name[100];
    char desc[100];
    char Gender[10];
    char Country[20];
    char Occupation[100];
    int Birth_year;
    int Age_death;
    Node *left;
    Node *right;
    Node()
    {
    	  Id =0;
        strcpy(desc, "None");
        strcpy(Gender, "None");
        strcpy(Country, "None");
        strcpy(Occupation, "None");
        Birth_year = 0;
        Age_death = 0;
        left = right = NULL;
	}
    Node(int id,char name[100],char d[100],char G[10],char count[20],char occu[100],int by,int ad)
    {
        Id = id;
        strcpy(Name, name);
        strcpy(desc, d);
        strcpy(Gender, G);
        strcpy(Country, count);
        strcpy(Occupation, occu);
        Birth_year = by;
        Age_death = ad;
        left = right = NULL;
    }
    void reg()
    {
         cout<<"<---:ADD NODE:--->"<<endl;
         cout<<"Add ID: ";
         cin>>Id;
         cout<<"\nAdd NAME: ";
         fflush(stdin);
         gets(Name);
         cout<<"\nAdd description: ";
         gets(desc);
         cout<<"\nAdd Gender: ";
         gets(Gender);
         cout<<"\nAdd Country: ";
         gets(Country);
         cout<<"\nAdd Occupation: ";
         gets(Occupation);
         cout<<"\nAdd Birth year";
         cin>>Birth_year;
         cout<<"\nAdd Age of death";
         cin>>Age_death;
    }
    int store_data()
   {
       if(Id==0)
       {
        cout<<"Data not initiallized"<<endl;
        return 0;
       }
       else
       {
       ofstream fout;
       fout.open("record.dat",ios::app|ios::binary);
       fout.write((char*)this,sizeof(*this));
       fout.close();
       return 1;
       }
   }
   void showdata()
    {
        cout << Id << endl;
        cout << Name << endl;
        cout << desc << endl;
        cout << Gender << endl;
        cout << Country << endl;
        cout << Occupation << endl;
        cout << Birth_year << endl;
        cout << Age_death << endl;
    }
};
class BST
{
    public:
    int arr[100];
    Node *root;
    Node temp;
    BST()
    {
        root =NULL;
    }
    void Insert_Node(Node *p)
    {
        Node *t = root;
        Node *r;
        if (root == NULL)
        {
            p->left = p->right = NULL;
            root = p;
            cout<<"Added succesfully"<<endl;
            return;
        }
        while (t != NULL)
        {
            r = t;
            if (p->Id < t->Id)
            {
                t = t->left;
            }
            else if (p->Id > t->Id)
            {
                t = t->right;
            }
            else
            {
                cout << "No duplicates allowed" << endl;
            }
        }
        if (p->Id < r->Id)
        {
            r->left = p;
    
        }
        else
        {
            r->right = p;
        }
       cout<<"Converted Succesfully"<<endl;    
    }
    bool isBST(Node * root,Node* min=NULL,Node * max=NULL)
   {
     if (root == NULL)
     {
      return true;
     }
     if (min != NULL && root->Id <= min->Id)
     {
      return false;
     }
      if (max != NULL && root->Id >= max->Id)
     {
      return false;
     }
     bool left = isBST(root->left,min,root);
     bool right = isBST(root->right,root,max);
     return left && right;
   }
    Node * Recursivesearch(Node *r, int key)
   {
      if (r== NULL)
      {
        return r;
      }
      if (r->Id== key)
      {
        return r;
      }
      else if (key< r->Id)
      {
        return Recursivesearch(r->left,key);
      }
      else 
      {
        return Recursivesearch(r->right,key);
      }
      
   }
   int height(Node *r)
   {
      if (r== NULL)
      {
        return 0;
      }
      else
      {
        int lheight=height(r->left);
        int rheight =height(r->right);
        if (lheight>rheight)
        {
            return lheight+1;
        }
        else
        {
            return rheight+1;
        }
        
      }
      
   }
   void Preorder(Node *r)
   {
   if(r){
           arr[i++]=r->Id;
			Preorder(r->left);	// left, root, right
			Preorder(r->right);
		}
   }
   int TakeInput(char str[])
   {
    InitWindow(850,450,"Managing");
    ClearBackground(BLACK);
    int number=0,j=0;
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
       
		ClearBackground(BLACK);
        DrawText("Enter ID to search: ",20,100,20,RAYWHITE);
        
         if(IsKeyPressed(KEY_SPACE))
        {
            return number;
        }
        if(IsKeyPressed(KEY_ZERO))
        {
            number = number*10;
            str[j++]='0';
        } 
        if(IsKeyPressed(KEY_ONE))
        {
            number = (number *10)+1;
            str[j++]='1';
        }  
        if(IsKeyPressed(KEY_TWO))
        {
            number = (number *10)+2;
            str[j++]='2';
        }  
        if(IsKeyPressed(KEY_THREE))
        {
            number = (number *10)+3;
            str[j++]='3';
        }  
        if(IsKeyPressed(KEY_FOUR))
        {
            number = (number *10)+4;
            str[j++]='4';
        }  
        if(IsKeyPressed(KEY_FIVE))
        {
            number = (number *10)+5;
            str[j++]='5';
        }  
        if(IsKeyPressed(KEY_SIX))
        {
         number = (number *10)+6;
         str[j++]='6';
        }  
        if(IsKeyPressed(KEY_SEVEN))
        {
            number = (number *10)+7;
            str[j++]='7';
        }  
        if(IsKeyPressed(KEY_EIGHT))
        {
        number = (number *10)+8;
        str[j++]='8';
        }  
        if(IsKeyPressed(KEY_NINE))
        {
         number = (number *10)+9;
         str[j++]='9';
        }  
        DrawText(str,MeasureText("Enter Id To search : ",20)+20,100,20,RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    
   }
   void in_order(Node* r,bool left,int x,int y) {		//inorder always couts in sorted manner
		if (r) {
			in_order(r->left,1,x-10,y+10);	// left, root, right
			if (left == true) {
				DrawRectangle(x, y, 10,10 , BLACK);
				DrawText( (to_string(r->Id)).c_str(), x , y, 5, RED);
				cout << "b:X"<<x<<"|Y:"<<y;

				
			}
			else {
				DrawRectangle(x , y, 10, 10, BLACK);
				cout << "c:X" << x << "|Y:" << y;
				DrawText((to_string(r->Id)).c_str(), x , y, 5, RED);
			}
			if (r->left != NULL)
				DrawLine(x, y, x - 10, y + 5, RED);
			if (r->right != NULL)
				DrawLine(x, y, x + 10, y + 5, RED);
		
			cout << "a,";
			in_order(r->right,0,x+10,y+10);
		}
	}
void display(int arr[],int height)
   {

       const int screenWidth = 800;
	const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Binary structure Tree");    
     while (!WindowShouldClose())
	{
		BeginDrawing();
       
		ClearBackground(BLACK);
             DrawRectangle(330, 30, 60, 30, RAYWHITE);//1 node
		DrawText(TextFormat("%i",arr[0]), 330+10, 30+10, 20, BLACK);
       DrawLine(360, 60, 290, 80,RAYWHITE );  
       DrawLine(360, 60, 420, 80,RAYWHITE );  

        DrawRectangle(250, 80, 60, 30, RAYWHITE);//2 node
		DrawText(TextFormat("%i",arr[1]), 250+10, 80+10, 20, BLACK);
      DrawLine(280, 110, 240, 140,RAYWHITE );  
       DrawLine(280, 110, 320, 140,RAYWHITE );


        DrawRectangle(400, 80, 60, 30, RAYWHITE);//3 node
		DrawText(TextFormat("%i",arr[2]), 400+10, 80+10, 20, BLACK);
        DrawLine(430, 110, 390, 140,RAYWHITE );  
       DrawLine(430, 110, 480, 140,RAYWHITE );



        DrawRectangle(200, 140, 60, 30, RAYWHITE);
		DrawText("55", 200+10, 140+10, 20, BLACK);
        
        DrawRectangle(280, 140, 60, 30, RAYWHITE);
		DrawText("80", 280+10, 140+10, 20, BLACK);
       
        DrawRectangle(360, 140, 60, 30, RAYWHITE);
		DrawText("105", 360+10, 140+10, 20, BLACK);
        
        DrawRectangle(450, 140, 60, 30, RAYWHITE);
		DrawText("120", 450+10, 140+10, 20, BLACK);
        
        DrawRectangle(200, 240, 60, 30, RAYWHITE);
		DrawText("55", 200+10, 140+10, 20, BLACK);
        
        DrawRectangle(280, 240, 60, 30, RAYWHITE);
		DrawText("80", 280+10, 140+10, 20, BLACK);
       
        DrawRectangle(360, 240, 60, 30, RAYWHITE);
		DrawText("105", 360+10, 140+10, 20, BLACK);
        
        DrawRectangle(450, 240, 60, 30, RAYWHITE);
		DrawText("120", 450+10, 140+10, 20, BLACK);
        
        DrawRectangle(20, 240, 60, 30, RAYWHITE);
		DrawText("55", 200+10, 140+10, 20, BLACK);
        
        DrawRectangle(120, 240, 60, 30, RAYWHITE);
		DrawText("80", 280+10, 140+10, 20, BLACK);
       
        DrawRectangle(530, 240, 60, 30, RAYWHITE);
		DrawText("105", 360+10, 140+10, 20, BLACK);
        
        DrawRectangle(600, 240, 60, 30, RAYWHITE);
		DrawText("120", 450+10, 140+10, 20, BLACK);
       

        
        EndDrawing();

	}
	CloseWindow();
   }
   void display_node_info(Node *r)
   {
       const int screenWidth = 800;
	const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Binary structure Tree");
    while (!WindowShouldClose())
	{
		BeginDrawing();
       
		ClearBackground(BLACK);
          DrawText("NAME: ", 100+10, 10, 20, RAYWHITE);
          DrawText(r->Name, 100+10, 40, 20, YELLOW);
          DrawText("Description: ", 100+10, 70, 20, RAYWHITE);
          DrawText(r->desc, 100+10, 100, 20, YELLOW);
          DrawText("Country: ", 100+10, 130, 20, RAYWHITE);
          DrawText(r->Country, 100+10, 170, 20, YELLOW);
          DrawText("Occupation: ", 100+10, 200, 20, RAYWHITE);
          DrawText(r->Occupation, 100+10, 240, 20, YELLOW);
          DrawText("Gender: ", 100+10, 270, 20, RAYWHITE);
          DrawText(r->Gender, 100+10, 300, 20, YELLOW);
          DrawText("Age: ", 100+10, 330, 20, RAYWHITE);
          DrawText(TextFormat("%i",r->Age_death), 100+10, 370, 20, YELLOW);

        
        EndDrawing();

	}
    CloseWindow();
   }
  
};
int main()
{
    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib ");
    SetTargetFPS(60);

	Camera2D camera = { 0 };
    camera.target = { 0, 0 };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    BST B;
    Node P;
  
    
     ifstream fin;
        fin.open("record.dat", ios::out|ios::binary);
        if (!fin)
        {
            cout << "File Not Found" << endl;
        }
        else
        {
            fin.read((char *)&P, sizeof(P));
            while (!fin.eof())
            {
                Node* temp = new Node(P.Id,P.Name,P.desc,P.Gender,P.Country,P.Occupation,P.Birth_year,P.Age_death);
                B.Insert_Node(temp);
                fin.read((char *)&P, sizeof(P));
            }

            fin.close();
        }
    B.Preorder(B.root);
    // int count =0;  // For displaying the node window
    //  while (!WindowShouldClose()) {

    //      camera.target = { GetMousePosition().x, GetMousePosition().y };      //  CAMERA
    //      camera.zoom += ((float)GetMouseWheelMove() * 0.05f);            //
    //      if (camera.zoom > 3.0f)                                         //
    //          camera.zoom = 3.0f;                                         //
    //      else if (camera.zoom < 0.1f)                                    //
    //         camera.zoom = 0.1f;                                         //  CAMERA


    //     BeginDrawing();
        
    //      BeginMode2D(camera);
	// 	ClearBackground(Color{ 186,200,90,255 });

	// 	DrawRectangle(10, 10, 50, 50, BLACK);


	// 		B.in_order(B.root, 0, screenWidth/2, 0);
	// 	if (count == 0) {
	// 		count++;
	// 	}

	// 	EndMode2D();
    //     EndDrawing();
    // }
   
   char arr[10]={'0'};
   
   int num =B.TakeInput(arr);
    Node *temp=B.Recursivesearch(B.root,num);
    if (temp == NULL)
    {
     cout<<"NULL"<<endl;
     return 0;
    }
    else
    B.display_node_info(temp);
    
        
    
    
   
	
}
       