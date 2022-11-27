#include <iostream>
#include <fstream>
#include <string>
#include<string.h>
#include<cctype>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
class Node
{
   public:
    char Id[10];
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
    	  strcpy(Id, "None");
        strcpy(desc, "None");
        strcpy(Gender, "None");
        strcpy(Country, "None");
        strcpy(Occupation, "None");
        Birth_year = 0;
        Age_death = 0;
        left = right = NULL;
	}
    Node(char id[10],char name[100],char d[100],char G[10],char count[20],char occu[100],int by,int ad)
    {
        strcpy(Id, id);
        strcpy(Id, name);
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
         gets(Id);
         cout<<"\nAdd NAME: ";
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
       if(Id=="Null")
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
            if (p->Age_death < t->Age_death)
            {
                t = t->left;
            }
            else if (p->Age_death > t->Age_death)
            {
                t = t->right;
            }
            else
            {
                cout << "No duplicates allowed" << endl;
            }
        }
        if (p->Age_death < r->Age_death)
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
     if (min != NULL && root->Age_death <= min->Age_death)
     {
      return false;
     }
      if (max != NULL && root->Age_death >= max->Age_death)
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
      if (r->Age_death== key)
      {
        return r;
      }
      else if (key< r->Age_death)
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
   void Inorder(Node *r)
   {
   if(r){
			Inorder(r->left);	// left, root, right
			r->showdata();
            cout<<endl;
			Inorder(r->right);
		}
   }
};
int main()
{
    Node P;
    BST B;
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
if (B.isBST(B.root,NULL,NULL))
        {
            cout<<"Yes its BST"<<endl;
        
        }
     cout<<B.height(B.root)<<endl;
     Node *t= B.Recursivesearch(B.root,40);
     t->showdata();  
        
}