#include "raylib.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <raymath.h>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
int screenwidth = 800;
int screenheight = 600;
void DisplayStack(int[]);
void TakeInput(int[], char[], int, int);
void DisplayTree(int[]);
void DisplayQueue(int[]);
void DisplayLinkedList(int[]);
void storing();
void sort(int[], int[], int);
void rsearch(int[], int[], int);
void load_searching_window(void);
/*
    ------------------------Sorting Algorithms------------------------------------
    1.MergeSort
    2.QuickSort
    3.RadixSort
    4.BubbleSort
    5.InsertionSort
    6.SelectionSort
    7.ModifiedSelectionSort
    8.CombSort
    9.CountSort
    10.ShellSort
    11.HeapSort
*/

int results[11][2];

int getGap(int i)
{
    i = (i * 10) / 13;
    if (i < 1)
        return 1;
    return i;
}
void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
class MinHeap
{
    int capacity;
    int size;
    int *heap;

public:
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    MinHeap(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        heap = (int *)malloc(capacity * sizeof(int));
    }
    void insert(int k)
    {
        if (size == capacity)
        {
            return;
        }
        int i = size;
        heap[size++] = k;
        while (i != 0 && heap[parent(i)] > heap[i])
        {
            Swap(&heap[i], &heap[parent(i)]);
            i = parent(i);
        }
    }
    int Delete()
    {
        results[10][0]++;
        if (size == 0)
        {
            return -1;
        }
        if (size == 1)
        {
            return heap[--size];
        }
        int root = heap[0];
        heap[0] = heap[--size];
        heapify(0);
        return root;
    }
    void heapify(int i)
    {
        results[10][0]++;
        results[10][1] += 2;
        int l = left(i);
        int r = right(i);
        int min = i;
        if (l < size && heap[min] > heap[l])
            min = l;
        if (r < size && heap[min] > heap[r])
            min = r;
        if (min != i)
        {
            Swap(&heap[i], &heap[min]);
            heapify(min);
        }
    }
    void BuildHeap(int array[], int size)
    {
        for (int i = 0; i < size; ++i)
            insert(array[i]);
    }
    int getSize() { return size; }
};
void HeapSortAscending(int arr[], int N)
{
    MinHeap obj(N);
    obj.BuildHeap(arr, N);
    for (int i = 0; i < N; ++i)
    {
        arr[i] = obj.Delete();
        results[10][0]++;
    }
}
int findMax(int arr[], int size)
{
    int max = arr[0];
    for (int i = 0; i < size; ++i)
    {
        results[2][1]++;
        results[2][0]++;
        max = max > arr[i] ? max : arr[i];
    }
    return max;
}
int findmax(int arr[], int size)
{
    int max = arr[0];
    for (int i = 0; i < size; ++i)
    {
        results[8][1]++;
        results[8][1]++;
        max = max > arr[i] ? max : arr[i];
    }
    return max;
}
void BubbleSort(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            results[3][0]++;
            if (arr[j] > arr[j + 1])
            {
                results[3][1]++;
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
void CountSort(int arr[], int size)
{
    int max = findmax(arr, size);
    int temp[max + 1] = {0};
    for (int i = 0; i < size; ++i)
    {
        results[8][0]++;
        temp[arr[i]]++;
    }
    for (int i = 0, j = 0; i < max + 1; ++i)
    {
        results[8][0]++;
        while (temp[i])
        {
            results[8][0]++;
            arr[j] = i;
            ++j;
            --temp[i];
        }
    }
}
void CountSortAscending(int arr[], int size, int exp)
{
    int output[size];
    int count[10] = {0};
    for (int i = 0; i < size; ++i)
    {
        results[2][0]++;
        count[arr[i] / exp % 10]++;
    }
    for (int i = 1; i < 10; ++i)
    {
        results[2][0]++;
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; --i)
    {
        results[2][0]++;
        output[--count[arr[i] / exp % 10]] = arr[i];
    }
    for (int i = 0; i < size; ++i)
    {
        results[2][0]++;
        arr[i] = output[i];
    }
}
void RadixSort(int arr[], int size)
{
    int max = findMax(arr, size);
    for (int exponent = 1; max / exponent > 0; exponent *= 10)
    {
        results[2][0]++;
        CountSortAscending(arr, size, exponent);
    }
}
int partition(int arr[], int low, int high)
{
    int i = low, j = high, pivot = arr[low];
    while (1)
    {
        //++results[1][0];

        while (arr[i] < pivot)
        {
            ++i;
            ++results[1][1];
            ++results[1][0];
        }
        while (arr[j] > pivot)
        {
            --j;
            ++results[1][1];
            ++results[1][0];
        }
        if (i < j)
            Swap(&arr[i], &arr[j]);
        else
            return j;
    }
}
void quickSort(int arr[], int low, int high)
{
    int pi;
    if (low < high)
    {
        ++results[1][0];
        pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void CombSort(int array[], int size)
{
    int gap = size;
    bool swap = true;
    while (gap != 1 || swap == true)
    {
        swap = false;
        gap = getGap(gap);
        results[7][1]++;
        ++results[7][0];
        for (int i = 0; i < size - gap; ++i)
        {
            results[7][0]++;
            results[7][1]++;
            if (array[i] > array[gap + i])
            {
                Swap(&array[i], &array[gap + i]);
                swap = true;
            }
        }
    }
}
void SelectionSort(int array[], int size)
{

    for (int i = 0; i < size - 1; ++i)
    {
        int min_index = i;
        for (int j = i + 1; j < size; ++j)
        {
            results[5][0]++;
            if (array[min_index] > array[j])
                min_index = j;
            results[5][1]++;
        }
        Swap(&array[min_index], &array[i]);
    }
}
void ModifiedSelection(int array[], int size)
{
    for (int i = 0, j = size - 1; i < j; i++, j--)
    {
        int max_index = i, min_index = i;
        for (int k = i; k <= j; ++k)
        {
            results[6][0]++;
            results[6][1] += 2;
            if (array[max_index] < array[k])
                max_index = k;
            if (array[min_index] > array[k])
                min_index = k;
        }
        Swap(&array[max_index], &array[j]);
        Swap(&array[min_index], &array[i]);
    }
}
void InsertionSort(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        results[4][0]++;
        while (j >= 0 && arr[j] > key)
        {
            results[4][0]++;
            results[4][1]++;
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}
void ShellSort(int array[], int size)
{
    int iter1, iter2, iter3;
    iter1 = iter2 = iter3 = 0;
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        //++iter1;
        for (int i = gap; i < size; ++i)
        {
            //++iter2;
            results[9][1]++;
            int key = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > key; j -= gap)
            {
                results[9][1]++;
                array[j] = array[j - gap];
                ++iter3;
            }
            array[j] = key;
        }
    }
    results[9][0] = iter1 + iter2 + iter3;
}
void Merge(int array[], int lower, int mid, int size)
{
    int size1 = mid - lower + 1;
    int size2 = size - mid;
    results[0][0] += size1 + size2;
    int subArray1[size1], subArray2[size2];
    for (int i = 0; i < size1; ++i)
        subArray1[i] = array[lower + i];
    for (int i = 0; i < size2; ++i)
        subArray2[i] = array[mid + 1 + i];
    int i = 0, j = 0, k = lower;
    while (i < size1 && j < size2)
    {
        if (subArray1[i] < subArray2[j])
        {
            array[k] = subArray1[i];
            ++i;
        }
        else
        {
            array[k] = subArray2[j];
            ++j;
        }
        ++k;
        ++results[0][1];
        ++results[0][0];
    }
    while (i < size1)
    {
        array[k] = subArray1[i];
        ++i;
        ++k;
        ++results[0][0];
    }
    while (j < size2)
    {
        array[k] = subArray2[j];
        ++j;
        ++k;
        ++results[0][0];
    }
}
void MergeSort(int array[], int l, int size)
{
    if (l < size)
    {
        //++results[0][0];
        int m = (l + (size - 1)) / 2;
        MergeSort(array, l, m);
        MergeSort(array, m + 1, size);
        Merge(array, l, m, size);
    }
}
//------------------------------------------------------------------------------//
class CircularQueue
{
public:
    int front, rear, *arr, n;
    CircularQueue(int n)
    {
        front = rear = -1;
        this->n = n;
        arr = (int *)malloc(n * sizeof(arr));
    }
    bool isFull()
    {
        return ((front == 0 && rear == n - 1) || (front == rear + 1));
    }
    void insert(int val)
    {
        if ((front == 0 && rear == n - 1) || (front == rear + 1))
        {
            // cout<<"Queue Overflow \n";
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
        arr[rear] = val;
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
        for (int i = 0; i < n; ++i)
            insert(array[i]);
    }
};
class NodeForSLL
{
public:
    NodeForSLL *next;
    int data;
    NodeForSLL(int a)
    {
        next = NULL;
        data = a;
    }
};
class NodeForDLL
{
public:
    NodeForDLL *next;
    NodeForDLL *prev;
    int data;
    NodeForDLL(int a)
    {
        prev = next = NULL;
        data = a;
    }
};
class NodeForCLL
{
public:
    NodeForCLL *next;
    int data;
    NodeForCLL()
    {
        next = NULL;
        data = 0;
    }
    NodeForCLL(int a)
    {
        data = a;
    }
};
class CLL
{
public:
    NodeForCLL *head;
    NodeForCLL *tail;
    CLL()
    {
        head = tail = NULL;
    }
    CLL(NodeForCLL *temp)
    {
        head = tail = temp;
    }
    void append(int a)
    {
        NodeForCLL *n = (NodeForCLL *)malloc(sizeof(NodeForCLL));
        n->data = a;
        tail->next = n;
        n->next = head;
        tail = n;
    }
    void Copy(int array[])
    {
        NodeForCLL *n = (NodeForCLL *)malloc(sizeof(NodeForCLL));
        n->data = array[0];
        head = n;
        n->next = NULL;
        tail = head;
        for (int i = 1; i < 10; ++i)
            append(array[i]);
    }
    void prepend(int a)
    {
        NodeForCLL *n = (NodeForCLL *)malloc(sizeof(NodeForCLL));
        n->data = a;
        tail->next = n;
        n->next = head;
        head = n;
    }

    bool AddUsingKey(int a, int key)
    {
        NodeForCLL *n = (NodeForCLL *)malloc(sizeof(NodeForCLL));
        n->data = a;
        if (tail->data == key)
        {
            append(n->data);
            return 1;
        }
        NodeForCLL *temp = head;
        while (temp != tail)
        {
            if (temp->data == key)
                break;
            temp = temp->next;
        }
        if (temp == tail)
            return 0;
        n->next = temp->next;
        temp->next = n;
        return 1;
    }
    bool deleteNode(int key)
    {
        if (head->data == key)
        {
            tail->next = head->next;
            head = head->next;
            return 1;
        }
        if (tail->data == key)
        {
            NodeForCLL *temp = head;
            while (temp->next != tail)
                temp = temp->next;
            temp->next = head;
            tail = temp;
            return 1;
        }
        NodeForCLL *temp = head->next;
        NodeForCLL *prev = head;
        do
        {
            if (temp->data == key)
                break;
            temp = temp->next;
            prev = prev->next;
        } while (temp != head);
        if (temp == head)
            return 0;
        prev->next = temp->next;
        return 1;
    }
};
class DLL
{
public:
    NodeForDLL *head;
    NodeForDLL *tail;
    DLL()
    {
        head = tail = NULL;
    }
    DLL(NodeForDLL *n)
    {
        head = tail = n;
    }
    void append(int a)
    {
        NodeForDLL *n = (NodeForDLL *)malloc(sizeof(NodeForDLL));
        n->data = a;
        tail->next = n;
        n->prev = tail;
        n->next = NULL;
        tail = n;
    }
    void Copy(int array[])
    {
        head = (NodeForDLL *)malloc(sizeof(NodeForDLL));
        head->data = array[0];
        tail = head;
        head->next = head->prev = NULL;
        for (int i = 1; i < 10; ++i)
            append(array[i]);
    }
    void prepend(int a)
    {
        NodeForDLL *n = (NodeForDLL *)malloc(sizeof(NodeForDLL));
        n->data = a;
        n->next = head;
        head->prev = n;
        n->prev = NULL;
        head = n;
    }
    void AddUsingKey(int a, int key)
    {
        NodeForDLL *n = (NodeForDLL *)malloc(sizeof(NodeForDLL));
        n->data = a;
        if (tail->data == key)
        {
            append(n->data);
            return;
        }
        NodeForDLL *temp = head;

        while (temp != NULL)
        {
            if (temp->data == key)
                break;
            temp = temp->next;
        }
        temp->next->prev = n;
        n->next = temp->next;
        n->prev = temp;
        temp->next = n;
    }
    bool DeleteNode(int key)
    {
        if (head->data == key)
        {
            head = head->next;
            head->prev = NULL;
            return 1;
        }
        if (tail->data == key)
        {
            tail = tail->prev;
            tail->next = NULL;
            return 1;
        }
        NodeForDLL *temp = head;
        while (temp != NULL)
        {
            if (temp->data == key)
                break;
            temp = temp->next;
        }
        if (temp == NULL)
            return 0;
        temp->prev->next = temp->next;
        temp = NULL;
        return 1;
    }
};
class SLL

{
public:
    NodeForSLL *head;
    SLL(NodeForSLL *n)
    {
        head = n;
        head->next = NULL;
    }
    SLL() { head = NULL; }
    void append(int a)
    {
        NodeForSLL *n = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        n->data = a;
        if (head == NULL)
        {
            head = n;
            return;
        }
        n->next = head;
        head = n;
    }
    NodeForSLL *get_head() { return head; }
    void Copy(int array[])
    {
        head = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        head->data = array[0];
        head->next = NULL;
        for (int i = 1; i < 10; ++i)
            prepend(array[i]);
    }
    void prepend(int a)
    {
        NodeForSLL *temp = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        NodeForSLL *n = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        n->data = a;
        temp->next = n;
        n->next = NULL;
    }
    void inBetween(int a, int key)
    {
        NodeForSLL *n = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        n->data = a;
        NodeForSLL *temp = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        temp = head;
        while (temp != NULL)
        {
            if (temp->data == key)
                break;
            temp = temp->next;
        }
        n->next = temp->next;
        temp->next = n;
    }
    bool deleteNode(int key)
    {
        NodeForSLL *temp = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        temp = head->next;
        NodeForSLL *prev = (NodeForSLL *)malloc(sizeof(NodeForSLL));
        prev = head;
        if (prev->data == key)
        {
            head = head->next;
            return true;
        }
        while (temp != NULL)
        {
            if (temp->data == key)
                break;
            prev = prev->next;
            temp = temp->next;
        }
        if (temp == NULL)
            return false;
        prev->next = temp->next;
        temp = NULL;
        return true;
    }
};
int X = 370, Y = 20;
int i = 0;
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
        Id = 0;
        strcpy(desc, "None");
        strcpy(Gender, "None");
        strcpy(Country, "None");
        strcpy(Occupation, "None");
        Birth_year = 0;
        Age_death = 0;
        left = right = NULL;
    }
    Node(int id, char name[100], char d[100], char G[10], char count[20], char occu[100], int by, int ad)
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
        cout << "<---:ADD NODE:--->" << endl;
        cout << "Add ID: ";
        cin >> Id;
        cout << "\nAdd NAME: ";
        gets(Name);
        cout << "\nAdd description: ";
        gets(desc);
        cout << "\nAdd Gender: ";
        gets(Gender);
        cout << "\nAdd Country: ";
        gets(Country);
        cout << "\nAdd Occupation: ";
        gets(Occupation);
        cout << "\nAdd Birth year";
        cin >> Birth_year;
        cout << "\nAdd Age of death";
        cin >> Age_death;
    }
    int store_data()
    {
        if (Id == 0)
        {
            cout << "Data not initiallized" << endl;
            return 0;
        }
        else
        {
            ofstream fout;
            fout.open("record.dat", ios::app | ios::binary);
            fout.write((char *)this, sizeof(*this));
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
        root = NULL;
    }
    void Insert_Node(Node *p)
    {
        Node *t = root;
        Node *r;
        if (root == NULL)
        {
            p->left = p->right = NULL;
            root = p;
            cout << "Added succesfully" << endl;
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
        cout << "Converted Succesfully" << endl;
    }
    bool isBST(Node *root, Node *min = NULL, Node *max = NULL)
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
        bool left = isBST(root->left, min, root);
        bool right = isBST(root->right, root, max);
        return left && right;
    }
    Node *Recursivesearch(Node *r, int key)
    {
        if (r == NULL)
        {
            return r;
        }
        if (r->Id == key)
        {
            return r;
        }
        else if (key < r->Id)
        {
            return Recursivesearch(r->left, key);
        }
        else
        {
            return Recursivesearch(r->right, key);
        }
    }
    int height(Node *r)
    {
        if (r == NULL)
        {
            return 0;
        }
        else
        {
            int lheight = height(r->left);
            int rheight = height(r->right);
            if (lheight > rheight)
            {
                return lheight + 1;
            }
            else
            {
                return rheight + 1;
            }
        }
    }
    void Preorder(Node *r)
    {
        if (r)
        {
            arr[i++] = r->Id;
            Preorder(r->left); // left, root, right
            Preorder(r->right);
        }
    }
    int delete_node_input(char str[])
    {
        InitWindow(850, 450, "Managing");
        ClearBackground(BLACK);
        int number = 0, j = 0;

        while (!WindowShouldClose())
        {
            BeginDrawing();

            ClearBackground(BLACK);
            DrawText("Enter ID to Delete: ", 20, 100, 20, RAYWHITE);

            if (IsKeyPressed(KEY_SPACE))
            {
                CloseWindow();
                return number;
            }
            if (IsKeyPressed(KEY_ZERO))
            {
                number = number * 10;
                str[j++] = '0';
            }
            if (IsKeyPressed(KEY_ONE))
            {
                number = (number * 10) + 1;
                str[j++] = '1';
            }
            if (IsKeyPressed(KEY_TWO))
            {
                number = (number * 10) + 2;
                str[j++] = '2';
            }
            if (IsKeyPressed(KEY_THREE))
            {
                number = (number * 10) + 3;
                str[j++] = '3';
            }
            if (IsKeyPressed(KEY_FOUR))
            {
                number = (number * 10) + 4;
                str[j++] = '4';
            }
            if (IsKeyPressed(KEY_FIVE))
            {
                number = (number * 10) + 5;
                str[j++] = '5';
            }
            if (IsKeyPressed(KEY_SIX))
            {
                number = (number * 10) + 6;
                str[j++] = '6';
            }
            if (IsKeyPressed(KEY_SEVEN))
            {
                number = (number * 10) + 7;
                str[j++] = '7';
            }
            if (IsKeyPressed(KEY_EIGHT))
            {
                number = (number * 10) + 8;
                str[j++] = '8';
            }
            if (IsKeyPressed(KEY_NINE))
            {
                number = (number * 10) + 9;
                str[j++] = '9';
            }
            DrawText(str, MeasureText("Enter Id To search : ", 20) + 20, 100, 20, RAYWHITE);
            EndDrawing();
        }
        return 0;
        CloseWindow();
    }
    int TakeInput(char str[])
    {
        InitWindow(850, 450, "Managing");
        ClearBackground(BLACK);
        int number = 0, j = 0;

        while (!WindowShouldClose())
        {
            BeginDrawing();

            ClearBackground(BLACK);
            DrawText("Enter ID to search: ", 20, 100, 20, RAYWHITE);

            if (IsKeyPressed(KEY_SPACE))
            {
                CloseWindow();
                return number;
            }
            if (IsKeyPressed(KEY_ZERO))
            {
                number = number * 10;
                str[j++] = '0';
            }
            if (IsKeyPressed(KEY_ONE))
            {
                number = (number * 10) + 1;
                str[j++] = '1';
            }
            if (IsKeyPressed(KEY_TWO))
            {
                number = (number * 10) + 2;
                str[j++] = '2';
            }
            if (IsKeyPressed(KEY_THREE))
            {
                number = (number * 10) + 3;
                str[j++] = '3';
            }
            if (IsKeyPressed(KEY_FOUR))
            {
                number = (number * 10) + 4;
                str[j++] = '4';
            }
            if (IsKeyPressed(KEY_FIVE))
            {
                number = (number * 10) + 5;
                str[j++] = '5';
            }
            if (IsKeyPressed(KEY_SIX))
            {
                number = (number * 10) + 6;
                str[j++] = '6';
            }
            if (IsKeyPressed(KEY_SEVEN))
            {
                number = (number * 10) + 7;
                str[j++] = '7';
            }
            if (IsKeyPressed(KEY_EIGHT))
            {
                number = (number * 10) + 8;
                str[j++] = '8';
            }
            if (IsKeyPressed(KEY_NINE))
            {
                number = (number * 10) + 9;
                str[j++] = '9';
            }
            DrawText(str, MeasureText("Enter Id To search : ", 20) + 20, 100, 20, RAYWHITE);
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
    void in_order(int i, int j, Node *r)
    { // inorder always couts in sorted manner
        if (r == NULL)
            return;
        DrawCircle(i, j, 20, GREEN);
        DrawText((to_string(r->Id)).c_str(), i - 4, j, 15, RAYWHITE);
        in_order(i - 40, j + 80, r->left);
        in_order(i + 40, j + 80, r->right);
        if (r->left != NULL)
            DrawLine(i, j, i - 40, j + 70, RAYWHITE);
        if (r->right != NULL)
            DrawLine(i, j, i + 40, j + 70, RAYWHITE);
    }
    // DrawText((to_string(r->Id)).c_str(), x+5, y+5, 5, RED);
    void display_BST()
    {
        const int screenWidth = 800;
        const int screenHeight = 500;

        InitWindow(screenWidth, screenHeight, "raylib ");
        SetTargetFPS(60);
        Camera2D camera = {0};
        camera.target = {0, 0};
        camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        int count = 0; // For displaying the node window
        while (!WindowShouldClose())
        {
            //  CAMERA
            camera.target = {GetMousePosition().x, GetMousePosition().y}; //  CAMERA
            camera.zoom += ((float)GetMouseWheelMove() * 0.05f);          //
            if (camera.zoom > 3.0f)                                       //
                camera.zoom = 3.0f;                                       //
            else if (camera.zoom < 0.1f)                                  //
                camera.zoom = 0.1f;

            BeginDrawing();

            BeginMode2D(camera);
            ClearBackground(BLACK);

            // DrawRectangle(10, 10, 50, 50, BLACK);

            in_order(screenWidth / 2, 0, root);
            if (count == 0)
            {
                count++;
            }

            EndMode2D();
            EndDrawing();
        }
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
            DrawText("NAME: ", 100 + 10, 10, 20, RAYWHITE);
            DrawText(r->Name, 100 + 10, 40, 20, YELLOW);
            DrawText("Description: ", 100 + 10, 70, 20, RAYWHITE);
            DrawText(r->desc, 100 + 10, 100, 20, YELLOW);
            DrawText("Country: ", 100 + 10, 130, 20, RAYWHITE);
            DrawText(r->Country, 100 + 10, 170, 20, YELLOW);
            DrawText("Occupation: ", 100 + 10, 200, 20, RAYWHITE);
            DrawText(r->Occupation, 100 + 10, 240, 20, YELLOW);
            DrawText("Gender: ", 100 + 10, 270, 20, RAYWHITE);
            DrawText(r->Gender, 100 + 10, 300, 20, YELLOW);
            DrawText("Age: ", 100 + 10, 330, 20, RAYWHITE);
            DrawText(TextFormat("%i", r->Age_death), 100 + 10, 370, 20, YELLOW);

            EndDrawing();
        }
        CloseWindow();
    }
    Node *delete_Node(Node *r, int key)
    {
        if (r == NULL)
        {
            return NULL;
        }
        if (key < r->Id)
        {
            r->left = delete_Node(r->left, key);
        }
        else if (key > r->Id)
        {
            r->right = delete_Node(r->right, key);
        }
        else
        {
            if (r->right == NULL)
            {
                Node *temp = r->left;
                delete r;
                return temp;
            }
            else if (r->left == NULL)
            {
                Node *temp = r->right;
                delete r;
                return temp;
            }
            else
            {
                Node *temp = Minvalue(r->right);
                r->Id = temp->Id;
                r->right = delete_Node(r->right, temp->Id);
            }
        }
        return r;
    }
    Node *Minvalue(Node *q)
    {
        Node *current = q;
        while (current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }
    int MainMenu(char str[])
    {
        InitWindow(850, 450, "Managing");
        ClearBackground(BLACK);
        int number = 0, j = 0;

        while (!WindowShouldClose())
        {
            BeginDrawing();

            ClearBackground(BLACK);
            DrawText("Enter Your Choice: ", 20, 100, 20, RAYWHITE);
            DrawText("Display BST:1 ", 20, 150, 20, RAYWHITE);
            DrawText("Search Node:2 ", 20, 200, 20, RAYWHITE);
            DrawText("Delete Node:3 ", 20, 250, 20, RAYWHITE);
            if (IsKeyPressed(KEY_SPACE))
            {
                CloseWindow();
                return number;
            }
            if (IsKeyPressed(KEY_ONE))
            {
                number = 1;
                str[j++] = '1';
            }
            if (IsKeyPressed(KEY_TWO))
            {
                number = 2;
                str[j++] = '2';
            }
            if (IsKeyPressed(KEY_THREE))
            {
                number = 3;
                str[j++] = '3';
            }
            DrawText(str, MeasureText("Enter Your Choice : ", 20) + 20, 100, 20, RAYWHITE);
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
};
void load_managing_window(void)
{
    InitWindow(1000, 1000, "Managing");
    SetTargetFPS(60);
    int array[10] = {0};
    char ch[100];
    bool once = 0;
    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
        DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
        if (!once)
        {
            EndDrawing();
            CloseWindow();
            TakeInput(array, ch, 1, 10);
            InitWindow(1000, 1000, "Managing");
            BeginDrawing();
            DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
            DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
            once = true;
        }
        DrawText("Values You Entered: ", 20, 121, 20, RAYWHITE);
        DrawText(ch, MeasureText("Values You Entered: ", 20) + 30, 121, 20, RAYWHITE);
        DrawText(
            "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Records in binary Search Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ", 20, 181, 20, RAYWHITE);
        if (IsKeyPressed(KEY_ONE))
        {
            EndDrawing();
            CloseWindow();
            DisplayStack(array);
            InitWindow(1000, 1000, "Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
            DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
            DrawText("Values You Entered: ", 20, 121, 20, RAYWHITE);
            DrawText(ch, MeasureText("Values You Entered: ", 20) + 30, 121, 20, RAYWHITE);
            DrawText(
                "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Records in binary Search Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ", 20, 181, 20, RAYWHITE);
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            EndDrawing();
            CloseWindow();
            DisplayQueue(array);
            InitWindow(1000, 1000, "Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
            DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
            DrawText("Values You Entered: ", 20, 121, 20, RAYWHITE);
            DrawText(ch, MeasureText("Values You Entered: ", 20) + 30, 121, 20, RAYWHITE);
            DrawText(
                "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Records in binary Search Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ", 20, 181, 20, RAYWHITE);
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            EndDrawing();
            CloseWindow();
            DisplayTree(array);
            InitWindow(1000, 1000, "Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
            DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
            DrawText("Values You Entered: ", 20, 121, 20, RAYWHITE);
            DrawText(ch, MeasureText("Values You Entered: ", 20) + 30, 121, 20, RAYWHITE);
            DrawText(
                "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Records in binary Search Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ", 20, 181, 20, RAYWHITE);
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            EndDrawing();
            CloseWindow();
            DisplayLinkedList(array);
            InitWindow(1000, 1000, "Managing Data Structures");
            BeginDrawing();
            DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
            DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
            DrawText("Values You Entered: ", 20, 121, 20, RAYWHITE);
            DrawText(ch, MeasureText("Values You Entered: ", 20) + 30, 121, 20, RAYWHITE);
            DrawText(
                "Select one of the following options: \n1)Display data in the form of stack\n2)Display Data in the form of queue\n3)Display Records in binary Search Tree\n4)Display Data in the form of Linked List\nEnter 1,2,3 or 4: ", 20, 181, 20, RAYWHITE);
        }
        EndDrawing();
    }
    CloseWindow();
}
void DisplayLinkedList(int array[])
{
    const int screenheight = 600;
    const int screenwidth = 1000;
    int i = 0, j = 0;
    SLL *hehe = (SLL *)malloc(sizeof(SLL));
    NodeForSLL *temp = (NodeForSLL *)malloc(sizeof(NodeForSLL));
    hehe->Copy(array);
    InitWindow(screenwidth, screenheight, "Linked Lists");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Select one of the following options\n1)Singly Linked List\n2)Doubly Linked List\n3)Circular linked list\nEnter the format in which you want to store the data: ", 10, 10, 20, RAYWHITE);
        if (IsKeyPressed(KEY_ONE))
        {
            EndDrawing();
            CloseWindow();
            InitWindow(screenwidth, screenheight, "Singly Linked List");
            // SetTargetFPS(60);
            while (!WindowShouldClose() && i < 10)
            {
                BeginDrawing();
                DrawText("Elements are inserted in the Singly Linked in to following order", 10, 230, 20, RAYWHITE);
                DrawRectangle(10 + j + 2, 300, 50, 50, RAYWHITE);
                if (i <= 8)
                {
                    DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                    DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                    DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                }
                DrawText(TextFormat("%i", array[i]), 20 + j, 325, 25, BLACK);
                if (IsKeyPressed(KEY_SPACE))
                {
                    j += 70;
                    ++i;
                }
                EndDrawing();
            }
            j = i = 0;
            int element = 0;
            Texture2D head = LoadTexture("resources/head.png");
            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                j = 0;
                temp = hehe->head;
                while (temp->next != NULL)
                {
                    DrawTexture(head, -15, 350, RAYWHITE);
                    DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                    DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                    DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                    DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                    DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                    j += 70;
                    temp = temp->next;
                }
                DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                if (IsKeyPressed(KEY_ONE))
                {
                    int code = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                        DrawText("Enter the Key: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the Key: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 49)
                            flag = true;
                        EndDrawing();
                    }
                    if (!hehe->deleteNode(element))
                        while (!IsKeyPressed(KEY_ENTER))
                        {
                            BeginDrawing();
                            DrawText("A Node with this key does not exist.\nPress enter to continue", 10, 160, 20, RAYWHITE);
                            EndDrawing();
                        }
                }
                if (IsKeyPressed(KEY_TWO))
                {
                    int code = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                        DrawText("Enter the Key: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the Key: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 50)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->append(element);
                }
                if (IsKeyPressed(KEY_THREE))
                {
                    int code = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                        DrawText("Enter the Key: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the Key: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 51)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->prepend(element);
                }
                if (IsKeyPressed(KEY_FOUR))
                {
                    int code = 0;
                    int key = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawText("Enter the Key after which you want to add Node: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            key *= 10;
                            key += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            key /= 10;
                        DrawText(TextFormat("%i", key), MeasureText("Enter the Key after which you want to add Node: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 52)
                            flag = true;
                        EndDrawing();
                    }
                    code = 0;
                    flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawText("Enter the data for new Node: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the data for new Node: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 51)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->inBetween(element, key);
                }
                EndDrawing();
            }

            CloseWindow();
            InitWindow(screenwidth, screenheight, "Linked Lists");
            BeginDrawing();
            DrawText("Select one of the following options\n1)Singly Linked List\n2)Doubly Linked List\n3)Circular linked list\nEnter the format in which you want to store the data: ", 10, 10, 20, RAYWHITE);
        }

        if (IsKeyPressed(KEY_TWO))
        {

            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            j = i = 0;

            while (!WindowShouldClose() && i < 10)
            {
                BeginDrawing();
                DrawText("Elements are inserted in the Doubly Linked List in to following order", 10, 230, 20, RAYWHITE);
                DrawRectangle(10 + j + 2, 300, 50, 50, RAYWHITE);
                if (i <= 8)
                {
                    DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                    DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                    DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                    DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                    DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                    DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                }

                DrawText(TextFormat("%i", array[i]), 20 + j, 325, 25, BLACK);
                if (IsKeyPressed(KEY_SPACE))
                {
                    j += 70;
                    ++i;
                }
                EndDrawing();
            }
            j = i = 0;
            int element = 0;
            Texture2D head = LoadTexture("resources/head.png");
            DLL *hehe = (DLL *)malloc(sizeof(DLL));
            NodeForDLL *temp = (NodeForDLL *)malloc(sizeof(NodeForDLL));
            hehe->Copy(array);
            head = LoadTexture("resources/head.png");
            Texture2D tail = LoadTexture("resources/tail.png");
            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                j = 0;
                temp = hehe->head;
                while (temp->next != NULL)
                {
                    DrawTexture(head, -15, 350, RAYWHITE);
                    DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                    DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                    DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                    DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                    DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                    DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                    DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                    DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                    j += 70;
                    temp = temp->next;
                }
                DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                DrawTexture(tail, j, 350, RAYWHITE);
                if (IsKeyPressed(KEY_ONE))
                {
                    int code = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                            DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                            DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                            DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                        DrawText("Enter the Key: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the Key: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 49)
                            flag = true;
                        EndDrawing();
                    }
                    if (!hehe->DeleteNode(element))
                        while (!IsKeyPressed(KEY_ENTER))
                        {
                            BeginDrawing();
                            DrawText("A Node with this key does not exist.\nPress enter to continue", 10, 160, 20, RAYWHITE);
                            EndDrawing();
                        }
                }
                if (IsKeyPressed(KEY_TWO))
                {
                    int code = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                            DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                            DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                            DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                        DrawText("Enter the Key: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the Key: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 50)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->prepend(element);
                }
                if (IsKeyPressed(KEY_THREE))
                {
                    int code = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                            DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                            DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                            DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                        DrawText("Enter the Key: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the Key: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 51)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->append(element);
                }
                if (IsKeyPressed(KEY_FOUR))
                {
                    int code = 0;
                    int key = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                            DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                            DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                            DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawText("Enter the Key after which you want to add Node: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            key *= 10;
                            key += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            key /= 10;
                        DrawText(TextFormat("%i", key), MeasureText("Enter the Key after which you want to add Node: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 52)
                            flag = true;
                        EndDrawing();
                    }
                    code = 0;
                    flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp->next != NULL)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 310, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 300, 85 + j, 310, RAYWHITE);
                            DrawLine(70 + j, 320, 85 + j, 310, RAYWHITE);

                            DrawLine(55 + j, 340, 75 + j, 330, RAYWHITE);
                            DrawLine(55 + j, 340, 75 + j, 350, RAYWHITE);
                            DrawLine(50 + j, 340, 90 + j, 340, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawText("Enter the data for new Node: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the data for new Node: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 51)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->AddUsingKey(element, key);
                }
                EndDrawing();
            }
            CloseWindow();
            InitWindow(screenwidth, screenheight, "Linked Lists");
            BeginDrawing();
            DrawText("Select one of the following options\n1)Singly Linked List\n2)Doubly Linked List\n3)Circular linked list\nEnter the format in which you want to store the data: ", 10, 10, 20, RAYWHITE);
        }
        if (IsKeyPressed(KEY_THREE))
        {
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            i = j = 0;
            int element = 0;
            NodeForCLL *temp = (NodeForCLL *)malloc(sizeof(NodeForCLL));
            CLL *hehe = (CLL *)malloc(sizeof(CLL));
            while (!WindowShouldClose() && i < 10)
            {
                BeginDrawing();
                DrawText("Elements are inserted in the Circular Linked List in to following order", 10, 230, 20, RAYWHITE);
                DrawRectangle(10 + j + 2, 300, 50, 50, RAYWHITE);
                if (i > 0)
                {
                    DrawLine(j - 20, 325, 15 + j, 325, RAYWHITE);
                    DrawLine(j, 315, 15 + j, 325, RAYWHITE);
                    DrawLine(j, 335, 15 + j, 325, RAYWHITE);
                }
                if (i > 8)
                {
                    DrawLine(37, 350, 37, 370, RAYWHITE);

                    DrawLine(37, 350, 17, 360, RAYWHITE);
                    DrawLine(37, 350, 57, 360, RAYWHITE);

                    DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                    DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                }
                DrawText(TextFormat("%i", array[i]), 20 + j, 325, 25, BLACK);
                if (IsKeyPressed(KEY_SPACE))
                {
                    j += 70;
                    ++i;
                }
                EndDrawing();
            }
            hehe->Copy(array);
            Texture2D head = LoadTexture("resources/head.png");
            Texture2D tail = LoadTexture("resources/tail.png");
            j = i = 0;
            element = 0;
            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("1)Remove a node from linked list\n2)Add a node in the start\n3)Add a node at the end of linked list\n4)Add a node in between", 10, 10, 20, RAYWHITE);
                j = 0;
                temp = hehe->head;
                while (temp != hehe->tail)
                {
                    DrawTexture(head, -15, 350, RAYWHITE);
                    DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                    DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                    DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                    DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                    DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                    j += 70;
                    temp = temp->next;
                }
                DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                DrawTexture(tail, j, 350, RAYWHITE);
                DrawLine(37, 350, 37, 370, RAYWHITE);

                DrawLine(37, 350, 17, 360, RAYWHITE);
                DrawLine(37, 350, 57, 360, RAYWHITE);

                DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                if (IsKeyPressed(KEY_ONE))
                {

                    int element = 0;
                    int code = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        j = 0;
                        temp = hehe->head;
                        while (temp != hehe->tail)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawLine(37, 350, 37, 370, RAYWHITE);

                        DrawLine(37, 350, 17, 360, RAYWHITE);
                        DrawLine(37, 350, 57, 360, RAYWHITE);

                        DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                        DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                        DrawText("Enter the key of node you want to delete: ", 10, 120, 20, RAYWHITE);
                        if (code >= 48 && code <= 58 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;

                        DrawText(TextFormat("%i", element), MeasureText("Enter the key of node you want to delete: ", 20) + 10, 120, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 49)
                            flag = true;

                        EndDrawing();
                    }
                    if (!hehe->deleteNode(element))
                        while (!IsKeyPressed(KEY_ENTER))
                        {
                            BeginDrawing();
                            DrawText("A Node with this key does not exist.\nPress enter to continue", 10, 160, 20, RAYWHITE);
                            EndDrawing();
                        }
                }
                if (IsKeyPressed(KEY_TWO))
                {
                    element = 0;
                    int code = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        j = 0;
                        temp = hehe->head;
                        while (temp != hehe->tail)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawLine(37, 350, 37, 370, RAYWHITE);

                        DrawLine(37, 350, 17, 360, RAYWHITE);
                        DrawLine(37, 350, 57, 360, RAYWHITE);

                        DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                        DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                        DrawText("Enter the key of node you want to Insert: ", 10, 120, 20, RAYWHITE);
                        if (code >= 48 && code <= 58 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;

                        DrawText(TextFormat("%i", element), MeasureText("Enter the key of node you want to Insert: ", 20) + 10, 120, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 50)
                            flag = true;

                        EndDrawing();
                    }
                    hehe->prepend(element);
                }
                if (IsKeyPressed(KEY_THREE))
                {
                    element = 0;
                    int code = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        j = 0;
                        temp = hehe->head;
                        while (temp != hehe->tail)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawLine(37, 350, 37, 370, RAYWHITE);

                        DrawLine(37, 350, 17, 360, RAYWHITE);
                        DrawLine(37, 350, 57, 360, RAYWHITE);

                        DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                        DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                        DrawText("Enter the key of node you want to Insert: ", 10, 120, 20, RAYWHITE);
                        if (code >= 48 && code <= 58 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;

                        DrawText(TextFormat("%i", element), MeasureText("Enter the key of node you want to Insert: ", 20) + 10, 120, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 51)
                            flag = true;

                        EndDrawing();
                    }
                    hehe->append(element);
                }
                if (IsKeyPressed(KEY_FOUR))
                {
                    int code = 0;
                    int key = 0;
                    element = 0;
                    bool flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp != hehe->tail)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);
                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawLine(37, 350, 37, 370, RAYWHITE);

                        DrawLine(37, 350, 17, 360, RAYWHITE);
                        DrawLine(37, 350, 57, 360, RAYWHITE);

                        DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                        DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                        DrawText("Enter the Key after which you want to add Node: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            key *= 10;
                            key += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            key /= 10;
                        DrawText(TextFormat("%i", key), MeasureText("Enter the Key after which you want to add Node: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 52)
                            flag = true;
                        EndDrawing();
                    }
                    code = 0;
                    flag = false;
                    while (code != 257 && !WindowShouldClose())
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        temp = hehe->head;
                        j = 0;
                        while (temp != hehe->tail)
                        {
                            DrawTexture(head, -15, 350, RAYWHITE);
                            DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                            DrawLine(50 + j, 325, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 315, 85 + j, 325, RAYWHITE);
                            DrawLine(70 + j, 335, 85 + j, 325, RAYWHITE);

                            DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                            j += 70;
                            temp = temp->next;
                        }
                        DrawRectangle(10 + j + 2, 300, 50, 50, GREEN);
                        DrawText(TextFormat("%i", temp->data), 20 + j, 325, 25, BLACK);
                        DrawTexture(tail, j, 350, RAYWHITE);
                        DrawLine(37, 350, 37, 370, RAYWHITE);

                        DrawLine(37, 350, 17, 360, RAYWHITE);
                        DrawLine(37, 350, 57, 360, RAYWHITE);

                        DrawLine(37, 370, 52 + j, 370, RAYWHITE);
                        DrawLine(52 + j, 350, 52 + j, 370, RAYWHITE);
                        DrawText("Enter the data for new Node: ", 10, 130, 20, RAYWHITE);
                        if (code >= 48 && code <= 57 && flag)
                        {
                            element *= 10;
                            element += code - 48;
                        }
                        if (IsKeyPressed(KEY_BACKSPACE))
                            element /= 10;
                        DrawText(TextFormat("%i", element), MeasureText("Enter the data for new Node: ", 20) + 10, 130, 20, RAYWHITE);
                        code = GetKeyPressed();
                        if (code != 51)
                            flag = true;
                        EndDrawing();
                    }
                    hehe->AddUsingKey(element, key);
                }
                EndDrawing();
            }
            CloseWindow();
            InitWindow(screenwidth, screenheight, "Linked Lists");
            BeginDrawing();
            DrawText("Select one of the following options\n1)Singly Linked List\n2)Doubly Linked List\n3)Circular linked list\nEnter the format in which you want to store the data: ", 10, 10, 20, RAYWHITE);
        }
        EndDrawing();
    }
    CloseWindow();
}
void DisplayQueue(int array[])
{
    const int screenheight = 600;
    const int screenwidth = 1000;
    InitWindow(screenwidth, screenheight, "Queues");
    int i = 0, j = 0;
    Texture2D front = LoadTexture("resources/front.png");
    Texture2D rear = LoadTexture("resources/rear.png");
    while (!WindowShouldClose() && i < 10)
    {
        BeginDrawing();
        DrawText("Elements are inserted in the queue in to following order", 10, 10, 20, RAYWHITE);
        DrawRectangle(10 + j, 300, 80, 50, RAYWHITE);
        DrawText(TextFormat("%i", array[i]), 10 + j + 40, 325, 30, BLACK);
        if (IsKeyPressed(KEY_SPACE))
        {
            j += 90;
            ++i;
        }
        EndDrawing();
    }
    ClearBackground(BLACK);
    bool flag = false;
    j = i = 0;
    int l = 0;
    int front_pos, rear_pos;
    int element;
    CircularQueue q(10);
    q.copy(array);
    while (!WindowShouldClose() && l < 10)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press p to Dequeue an element\n\nEnter an element to Enqueue: ", 10, 10, 20, RAYWHITE);
        front_pos = q.front * 90;
        rear_pos = q.rear * 90;
        DrawTexture(front, 10 + front_pos, 300 + (float)front.width, RAYWHITE);
        DrawTexture(rear, 10 + rear_pos, 300 + (float)front.width, RAYWHITE);
        int f = q.front, r = q.rear;
        if (f <= r)
        {
            while (f <= r)
            {
                DrawRectangle(10 + f * 90, 300, 80, 50, GREEN);
                DrawText(TextFormat("%i", q.arr[f]), 50 + f * 90 - 30, 325, 30, BLACK);
                ++f;
            }
        }
        else
        {
            while (f <= q.n - 1)
            {
                DrawRectangle(10 + f * 90, 300, 80, 50, GREEN);
                DrawText(TextFormat("%i", q.arr[f]), 50 + f * 90 - 30, 325, 30, BLACK);
                ++f;
            }
            f = 0;
            while (f <= r)
            {
                DrawRectangle(10 + f * 90, 300, 80, 50, GREEN);
                DrawText(TextFormat("%i", q.arr[f]), 50 + f * 90 - 30, 325, 30, BLACK);
                ++f;
            }
        }
        int hehe;
        if (IsKeyPressed(KEY_P))
        {
            flag = true;
            hehe = q.Delete();
            element = 0;
        }
        if (flag)
        {
            DrawText(TextFormat("Element Dequeued: %i", hehe), 10, 35, 20, RAYWHITE);
            DrawText("Remaining Queue: ", 10, 160, 20, RAYWHITE);
        }
        if (q.isFull())
        {
            DrawText("Queue Full!", MeasureText("Enter an element to Enqueue: ", 20) + 10, 70, 20, RAYWHITE);
        }
        else
        {
            if (IsKeyPressed(KEY_ZERO))
                element *= 10;
            if (IsKeyPressed(KEY_ONE))
            {
                element *= 10;
                element += 1;
            }
            if (IsKeyPressed(KEY_TWO))
            {
                element *= 10;
                element += 2;
            }
            if (IsKeyPressed(KEY_THREE))
            {
                element *= 10;
                element += 3;
            }
            if (IsKeyPressed(KEY_FOUR))
            {
                element *= 10;
                element += 4;
            }
            if (IsKeyPressed(KEY_FIVE))
            {
                element *= 10;
                element += 5;
            }
            if (IsKeyPressed(KEY_SIX))
            {
                element *= 10;
                element += 6;
            }
            if (IsKeyPressed(KEY_SEVEN))
            {
                element *= 10;
                element += 7;
            }
            if (IsKeyPressed(KEY_EIGHT))
            {
                element *= 10;
                element += 8;
            }
            if (IsKeyPressed(KEY_NINE))
            {
                element *= 10;
                element += 9;
            }
            DrawText(TextFormat("%i", element), MeasureText("Enter an element to Enqueue: ", 20) + 10, 70, 20, RAYWHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
                q.insert(element);
                element = 0;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}
void DisplayTree(int array[])
{
    BST B;
    Node P;
    ifstream fin;
    fin.open("record.dat", ios::out | ios::binary);
    if (!fin)
    {
        cout << "File Not Found" << endl;
    }
    else
    {
        fin.read((char *)&P, sizeof(P));
        while (!fin.eof())
        {
            Node *temp = new Node(P.Id, P.Name, P.desc, P.Gender, P.Country, P.Occupation, P.Birth_year, P.Age_death);
            B.Insert_Node(temp);
            fin.read((char *)&P, sizeof(P));
        }

        fin.close();
    }
    B.Preorder(B.root);
    char arr3[10] = {'0'};
    while (1)
    {
        int choice = B.MainMenu(arr3);
        if (choice == 1)
        {
            B.display_BST();
        }
        else if (choice == 2)
        {
            char arr[10] = {'0'};
            int num = B.TakeInput(arr);
            Node *temp = B.Recursivesearch(B.root, num);
            if (temp == NULL)
            {
                cout << "NULL" << endl;
                // return 0;
            }
            else
                B.display_node_info(temp);
        }
        else if (choice == 3)
        {
            char arr2[10] = {'0'};
            int num = B.delete_node_input(arr2);
            cout << num;
            B.delete_Node(B.root, num);
        }
        else
        {
            cout << "Wrong input" << endl;
        }
        if (IsKeyPressed(KEY_ESCAPE))
            break;
    }
}
void TakeInput(int array[], char str[], int which, int n)
{
    InitWindow(1000, 1000, "Managing");
    ClearBackground(BLACK);

    int i = 0;
    int j = 0;
    while (!WindowShouldClose() && i < n)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if (which == 1)
            DrawText("MANAGING Data Structures", 350, 20, 30, RAYWHITE);
        if (which == 2)
            DrawText("Sorting", 350, 20, 30, RAYWHITE);
        if (which == 3)
            DrawText("Searching", 350, 20, 30, RAYWHITE);
        DrawText("Input random values to store: ", 20, 100, 20, RAYWHITE);
        int code = GetKeyPressed();
        if (code >= 48 && code <= 57)
        {
            array[i] *= 10;
            array[i] += code - 48;
            str[j] = (char)code;
            ++j;
            str[j] = '\0';
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            ++i;
            str[j++] = ' ';
            str[j] = '\0';
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            array[i] /= 10;
            str[j - 1] = '\0';
            --j;
        }
        DrawText(str, MeasureText("Input random values to store: ", 20) + 20, 100, 20, RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
void DisplayStack(int array[])
{
    SetTargetFPS(144);
    const int screenheight = 600;
    const int screenwidth = 1000;
    InitWindow(screenwidth, screenheight, "Stacks");
    int j = 30;
    int i = 0;
    Texture2D top = LoadTexture("resources/top.png");
    Vector2 pos = {200 - (float)top.width, 540};
    while (!WindowShouldClose() && i < 10)
    {
        BeginDrawing();
        DrawText("Elements are pushed in the following order", 10, 10, 20, RAYWHITE);

        DrawRectangle(200, 600 - j, 250, 30, RAYWHITE);
        DrawText(TextFormat("%i", array[i]), 280, 600 - j + 4, 30, BLACK);
        if (IsKeyPressed(KEY_SPACE))
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
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press p to pop an element\n\nEnter an element to push into stack: ", 10, 10, 20, RAYWHITE);
        while (i < l)
        {
            DrawRectangle(200, 600 - j, 250, 30, GREEN);
            DrawText(TextFormat("%i", array[i]), 280, 600 - j + 4, 30, BLACK);
            j += 35;
            pos.y -= 35.0f;
            ++i;
        }

        if (l == 10)
        {
            DrawText("Stack overflow!", MeasureText("Enter an element to push into stack: ", 20) + 10, 70, 20, RAYWHITE);
        }
        else
        {
            int code = GetKeyPressed();
            if (code >= 48 && code <= 57)
            {
                array[l] *= 10;
                array[l] += code - 48;
            }
            if (IsKeyPressed(KEY_BACKSPACE))
                array[l] /= 10;
            DrawText(TextFormat("%i", array[l]), MeasureText("Enter an element to push into stack: ", 20) + 10, 70, 20, RAYWHITE);
            if (IsKeyPressed(KEY_ENTER))
                ++l;
        }
        if (IsKeyPressed(KEY_P))
        {
            temp = array[l - 1];
            array[l - 1] = 0;
            --l;
            flag = true;
        }
        if (flag)
        {
            DrawText(TextFormat("Element Popped: %i", temp), 10, 35, 20, RAYWHITE);
            DrawText("Remaining Stack: ", 10, 160, 20, RAYWHITE);
        }
        i = 0;
        DrawTextureV(top, pos, RAYWHITE);
        pos.y = 570.0f;
        j = 30;
        EndDrawing();
    }
    CloseWindow();
}

void storing()
{
    fstream file;
    file.open("hemlo.txt", ios::in);
    char c;
    int wcount = 0, i = 0;

    if (file.is_open())
    {
        while (file >> noskipws >> c)
        {
            if (c == ' ')
            {
                wcount++;
            }
        }
    }

    file.close();
    file.open("hemlo.txt", ios::in);
    int arr[wcount], index[wcount];

    for (int j = 0; j < wcount; j++)
    {
        arr[j] = 0;
        index[j] = j + 1;
    }

    i = 0;

    while (file >> noskipws >> c)
    {
        if (c == ' ')
        {
            i++;
        }

        cout << c;

        if (c != ' ')
        {
            int num = int(c);
            arr[i] = arr[i] + c;
        }
    }

    file.close();
    sort(arr, index, wcount);
    cout << endl;
}
void sort(int arr[], int index[], int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
                Swap(&index[j], &index[j + 1]);
            }
        }
    }

    rsearch(arr, index, x);
}
void rsearch(int arr[], int index[], int x)
{
    float sumX = 0.0, sumX2 = 0.0, sumY = 0.0, sumXY = 0.0, a = 0.0, b = 0.0;
    int y[x];

    for (int i = 0; i < x; i++)
    {
        y[i] = i;
    }

    for (int i = 0; i < x; i++)
    {
        sumX = sumX + arr[i];
        sumX2 = sumX2 + arr[i] * arr[i];
        sumY = sumY + y[i];
        sumXY = sumXY + arr[i] * y[i];
    }

    b = (x * sumXY - sumX * sumY) / (x * sumX2 - sumX * sumX);
    a = (sumY - b * sumX) / x;

    int num = 0;
    char word[45];

    for (int i = 0; i < 45; i++)
    {
        word[i] = '\0';
    }
    InitWindow(1000, 1000, "Searching");
    int k = 0;
    while (!IsKeyPressed(KEY_ENTER) && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Enter the word you want to search in the file: ", 10, 100, 20, RAYWHITE);
        int i = GetCharPressed();
        if (i >= 97 && i <= 122)
        {
            word[k++] = i;
            word[k] = '\0';
        }

        if (IsKeyPressed(KEY_BACKSPACE))
            word[--k] = '\0';
        DrawText(word, 10 + MeasureText("Enter the word you want to search in the file: ", 20), 100, 20, RAYWHITE);
        EndDrawing();
    }
    int w = 0;

    while (word[w] != '\0')
    {
        int y = int(word[w]);
        num = num + y;
        w++;
    }

    int pos = (num * b) + a;

    if (pos < 0)
        pos = 0;
    if (pos > x)
        pos = x;

    w = 0;
    int p = 0, freq = 0;
    bool flag;
    if (arr[pos] <= num)
    {
        for (int q = pos; q < x; q++)
        {
            w++;
            if (arr[q] == num)
            {
                p = q;
                while (arr[p] == num)
                {
                    p--;
                }
                p++;
                break;
            }
        }
    }

    else if (arr[pos] > num)
    {
        for (int q = pos; q > 0; q--)
        {
            w++;
            if (arr[q] == num)
            {
                p = q;
                while (arr[p] == num)
                {
                    p--;
                }
                p++;
                break;
            }
        }
    }
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Positions: ", 10, 150, 20, RAYWHITE);
        int temp = MeasureText("Positions", 20);
        int multiplier = 1;
        while (arr[p] == num)
        {
            DrawText(TextFormat("%i", index[p]), temp+10+multiplier*10, 150, 20, RAYWHITE);
            ++multiplier;
            temp += MeasureText(TextFormat("%i", index[p]), 20);
            DrawText(",", MeasureText(TextFormat("%i", index[p]), 20) + 2, 150, 20, RAYWHITE);
            p++;
            freq++;
        }
        DrawText(TextFormat("Frequency of word: %i", freq), 10, 180, 20, RAYWHITE);
        DrawText(TextFormat("Number of Comparisions: %i", w), 10, 210, 20, RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}

void load_documentation_window(void)
{
    InitWindow(1000, 1000, "Documentations");
    SetTargetFPS(60);

    Rectangle forbst = {330.0f, 330.0f, 10.0f + 330.0f, 600.0f};
    Rectangle foravl = {330.0f, 330.0f, 10.0f + 330.0f + 330.0f, 600.0f};
    bool once = false;
    Texture2D loader;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Select any one of the options: ", 20, 100, 20, RAYWHITE);
        DrawText("Documentations", 470, 20, 30, RAYWHITE);
        DrawText("1) Stacks\n2) Queues\n3) Linked Lists\n4) Trees", 20, 140, 20, RAYWHITE);

        if (IsKeyPressed(KEY_ONE))
        {

            while (!WindowShouldClose())
            {
                loader = LoadTexture("resources/stackimage.png");

                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Stacks", 470, 10, 30, RAYWHITE);
                DrawText("Stack is a linear data structure which follows a particular order in which the operations are\n performed. The order may be LIFO(Last In First Out) or FILO(First In Last Out)", 20, 100, 20, RAYWHITE);
                DrawText("There are many real-life examples of a stack. Consider an example of plates stacked over\n one another in the canteen. The plate which is at the top is the first one to be\nremoved, i.e. the plate which has been placed at the bottommost position remains \nin the stack for the longest period of time. So, it can be simply seen to follow LIFO(Last In First Out)/FILO(First In Last Out) order.", 20, 200, 20, RAYWHITE);
                DrawTexture(loader, 30, 400, RAYWHITE);
                EndDrawing();
                once = true;
            }
        }
        if (IsKeyPressed(KEY_TWO) && once)
        {
            while (!WindowShouldClose())
            {
                loader = LoadTexture("resources/queueimage.png");
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Queue", 470, 10, 30, RAYWHITE);
                DrawText("A queue is defined as a linear data structure that is open at both ends and \nthe operations are performed in First In First Out (FIFO) order.\nWe define a queue to be a list in which all additions to the list are made at one end, and all \ndeletions from the list are made at the other end.  The element which is first pushed into the \norder, the operation is first performed on that.", 20, 100, 20, RAYWHITE);
                DrawText("Like stacks, Queues can also be represented in an array: \nIn this representation, the Queue is implemented using the array. \nVariables used in this case are:", 20, 290, 20, RAYWHITE);
                DrawText("Queue Representation: ", 20, 400, 30, RAYWHITE);

                DrawText("Queue: the name of the array storing queue elements.", 60, 450, 20, RAYWHITE);
                DrawText("Front: the index where the first element is stored in the array representing the queue.", 60, 480, 20, RAYWHITE);
                DrawText("Rear: the index where the last element is stored in an array representing the queue.", 60, 510, 20, RAYWHITE);
                DrawTexture(loader, 30, 600, RAYWHITE);
                EndDrawing();
            }
        }

        if (IsKeyPressed(KEY_THREE))
        {
            while (!WindowShouldClose())
            {
                loader = LoadTexture("resources/llimage.png");
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Linked Lists", 400, 10, 30, RAYWHITE);
                DrawText("A linked list consists of nodes where each node contains a data field and \na reference(link) to the next node in the list.", 20, 100, 20, RAYWHITE);
                DrawText("It is a linear data structure, in which the elements are not stored at \ncontiguous memory locations.", 20, 200, 20, RAYWHITE);
                DrawText("There are three types of linked lists: ", 20, 300, 20, RAYWHITE);
                DrawText("1)Singly Linked List: Each node links to only the next node in the sequence\n2)Doubly Linked List: Each node links to the next as well as previous node in the sequence\n3)Circular Linked List: The last node links to the first node", 20, 350, 20, RAYWHITE);
                DrawTexture(loader, 30, 600, RAYWHITE);
                EndDrawing();
            }
            once = true;
        }
        if (IsKeyPressed(KEY_FOUR))
        {
            while (!WindowShouldClose())
            {

                loader = LoadTexture("resources/bst.png");
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Trees", 10, 10, 30, RAYWHITE);
                DrawTexture(loader, 10, 600, RAYWHITE);
                DrawText("A tree is a nonlinear data structure, compared to arrays, linked lists, stacks and queues \nwhich are linear data structures. \nA tree can be empty with no nodes or a tree is a structure consisting of one node called the \nroot and zero or one or more subtrees.", 10, 70, 20, RAYWHITE);
                DrawText("Binary Search Trees", 10, 220, 30, RAYWHITE);
                DrawText("Binary Search Tree is a node-based binary tree data structure which has the following \nproperties:", 10, 260, 20, RAYWHITE);
                DrawText("1)The left subtree of a node contains only nodes with keys lesser than the node’s key.\n2)The right subtree of a node contains only nodes with keys greater than the node’s key.\n3)The left and right subtree each must also be a binary search tree.", 10, 310, 20, RAYWHITE);
                DrawText("AVL Trees", 10, 400, 30, RAYWHITE);
                DrawText("Similarly, an AVL TREE is defined as a height balanced binary search tree in which each node \nis associated with a balance factor which is calculated by subtracting the height of \nleft subtree and height of right subtree", 10, 450, 20, RAYWHITE);
                int hehe = loader.width;
                loader = LoadTexture("resources/avl.png");
                DrawTexture(loader, hehe + 30, 600, RAYWHITE);
                DrawText("AVL TREE", hehe + 300, 500 + loader.height + 60, 20, BLACK);
                EndDrawing();
            }
            once = true;
        }
        EndDrawing();
    }

    CloseWindow();
}
void load_sorting_window(void)
{
    InitWindow(1000, 1000, "Sorting");
    SetTargetFPS(60);
    int array[10] = {0};
    char ch[100];
    int sorted[10] = {0};
    bool once = false;
    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("SORTING DATA", 350, 20, 30, RAYWHITE);
        if (!once)
        {
            EndDrawing();
            CloseWindow();
            TakeInput(array, ch, 2, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            MergeSort(sorted, 0, 9);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            BubbleSort(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            InsertionSort(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            CountSort(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            ShellSort(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            SelectionSort(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            ModifiedSelection(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            HeapSortAscending(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            CombSort(sorted, 10);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            quickSort(sorted, 0, 9);
            for (int i = 0; i < 10; ++i)
                sorted[i] = array[i];
            RadixSort(sorted, 10);
            InitWindow(1000, 1000, "Managing");
            BeginDrawing();
            DrawText("Sorting DATA", 350, 20, 30, RAYWHITE);
            DrawText("Input 10 random values to store: ", 20, 100, 20, RAYWHITE);
            once = true;
        }
        DrawText("Sorted array: ", 20, 140, 20, RAYWHITE);
        int j = 0;
        for (int i = 0; i < 10; ++i)
        {
            if (i == 9)
                DrawText(TextFormat("%i", sorted[i]), MeasureText("Sorted array: ", 20) + 10 + j + 20, 140, 20, RAYWHITE);
            else
                DrawText(TextFormat("%i,", sorted[i]), MeasureText("Sorted array: ", 20) + 10 + j + 20, 140, 20, RAYWHITE);
            j += 30;
        }
        DrawRectangle(20, 200, screenwidth - 50, screenheight - 30, RAYWHITE);
        DrawLine(21, 250, screenwidth - 51, 250, BLACK);
        DrawText("Sorting Algorithm", 30, 210, 25, BLACK);
        DrawText("Iterations", 400, 210, 25, BLACK);
        DrawText("Comparisions", 700, 210, 25, BLACK);
        DrawLine(350, 200, 350, screenheight - 30, BLACK);
        DrawLine(650, 200, 650, screenheight - 30, BLACK);
        DrawLine(350, 200, 350, screenheight - 30, BLACK);
        DrawLine(21, 300, screenwidth - 51, 300, BLACK);
        for (int i = 0; i < 10; ++i)
        {
            DrawLine(21, 300 + i * 70, screenwidth - 51, 300 + i * 70, BLACK);
        }
        DrawText("1)Merge Sort", 20, 270, 20, BLACK);
        DrawText("2)Quick Sort", 20, 340, 20, BLACK);
        DrawText("3)Radix Sort", 20, 410, 20, BLACK);
        DrawText("4)Bubble Sort", 20, 480, 20, BLACK);
        DrawText("5)Insertion Sort", 20, 550, 20, BLACK);
        DrawText("6)Selection Sort", 20, 620, 20, BLACK);
        DrawText("7)Modified Selection Sort", 20, 690, 20, BLACK);
        DrawText("8)Comb Sort", 20, 760, 20, BLACK);
        DrawText("9)Count Sort", 20, 830, 20, BLACK);
        DrawText("10)Shell Sort", 20, 900, 20, BLACK);
        DrawText("11)Heap Sort", 20, 950, 20, BLACK);
        for (int i = 0; i < 10; ++i)
        {
            DrawText(TextFormat("%i", results[i][0]), 365, 270 + i * 70, 20, BLACK);
            DrawText(TextFormat("%i", results[i][1]), 680, 270 + i * 70, 20, BLACK);
        }
        DrawText(TextFormat("%i", results[10][0]), 365, 950, 20, BLACK);
        DrawText(TextFormat("%i", results[10][1]), 680, 950, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
}
int main(void)

{
    int choice = 4;
    InitWindow(screenwidth, screenheight, "Data Structures Project");
    SetTargetFPS(60);
    Texture2D logo = LoadTexture("resources/FAST_logo-removebg-preview.png");
    float logo_width = logo.width / 2.5f;
    float logo_height = logo.height;
    float text_width = 50.0f;
    float text_height = 120.0f;
    Rectangle SourceRec = {0.0f, 0.0f, logo_width - 20, logo_height};
    Rectangle managing = {text_width, text_height, (float)MeasureText("Managing Data Structures", 30), 40};
    Rectangle searching = {text_width, text_height + 50, (float)MeasureText("Searching", 30), 40};
    Rectangle sorting = {text_width, text_height + 100, (float)MeasureText("Sorting", 30), 40};
    for (int i = 0; i < 11; ++i)
    {
        results[i][0] = 0;
        results[i][1] = 0;
    }
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(logo, SourceRec, Vector2{screenwidth - logo_width + 20, 0}, RAYWHITE);
        DrawText("Searching, Sorting & Managing Data Structures.", 150, 10, 20, RAYWHITE);
        DrawText("Muhammad Humza (21k-3293)", screenwidth - MeasureText("Muhammad Humza (21k-XXXX)", 20) - 10, screenheight - 20, 20, RAYWHITE);
        DrawText("Yaazir Mehdi (21k-3460)", screenwidth - MeasureText("Muhammad Humza (21k-XXXX)", 20) - 10, screenheight - 40, 20, RAYWHITE);
        DrawText("Bilal Hassan (21k-4669)", screenwidth - MeasureText("Muhammad Humza (21k-XXXX)", 20) - 10, screenheight - 60, 20, RAYWHITE);
        DrawText("Click on anyone of the following options:", 10.0f, 70.0f, 20, RAYWHITE);
        DrawText("Made By:", screenwidth - MeasureText("Muhammad Humza (21k-3293)", 20) - 10, screenheight - 80, 20, RAYWHITE);
        DrawRectangleRec(managing, BLACK);
        DrawRectangleRec(searching, BLACK);
        DrawRectangleRec(sorting, BLACK);
        DrawText("1) Managing Data Structures", 52.0f, 121.0f, 20, RAYWHITE);
        DrawText("2) Sorting", text_width, text_height + 50 + 1, 20, RAYWHITE);
        DrawText("3) Searching", text_width, text_height + 100 + 1, 20, RAYWHITE);
        DrawText("4) Documentations", text_width, text_height + 151, 20, RAYWHITE);
        if (IsKeyPressed(KEY_ONE))
        {
            choice = 1;
            break;
        }
        if (IsKeyPressed(KEY_TWO))
        {
            choice = 2;
            break;
        }
        if (IsKeyPressed(KEY_THREE))
        {
            choice = 3;
            break;
        }
        if (IsKeyPressed(KEY_FOUR))
        {
            choice = 4;
            break;
        }
        EndDrawing();
    }
    screenwidth = screenheight = 1000;
    CloseWindow();
    if (choice == 1)
        load_managing_window();
    else if (choice == 2)
        load_sorting_window();
    else if (choice == 3)
        load_searching_window();
    else if (choice == 4)
        load_documentation_window();
}
void load_searching_window(void)
{
    storing();
    main();
}