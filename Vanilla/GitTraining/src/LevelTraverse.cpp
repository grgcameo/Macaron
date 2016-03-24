#include "stdafx.h"
#include <iostream>


struct Node
{
    int data;
    Node *left;
    Node *right;
};
Node *Root;
 
Node **Queue;
int QSize;
int head,tail;
 
void InitQueue(int size)
{
    QSize=size;
    Queue=(Node **)malloc(QSize*sizeof(Node *));
    head=tail=0;
}
 
void FreeQueue()
{
    free(Queue);
}
 
bool Insert(Node *data)
{
    if ((tail+1) % QSize == head) {
        return false;
    }
    Queue[tail]=data;
    tail=(tail+1) % QSize;
    return true;
}
 
Node *Delete()
{
    Node *data;
 
    if (head==tail) {
        return NULL;
    }
    data=Queue[head];
    head=(head+1) % QSize;
    return data;
}
 
void InitTree(int data)
{
    Root=(Node *)malloc(sizeof(Node));
    Root->data=data;
}
 
Node *AddChild(Node *Parent,int data,bool bLeft)
{
    Node *New;
 
    New=(Node *)malloc(sizeof(Node));
    New->data=data;
    New->left=NULL;
    New->right=NULL;
    if (bLeft) {
        Parent->left=New;
    } else {
        Parent->right=New;
    }
    return New;
}
 
void FreeTree(Node *R)
{
    if (R->left) FreeTree(R->left);
    if (R->right) FreeTree(R->right);
    free(R);
}
 
void LevelOrder(Node *R)
{
    Node *tNode;
 
    Insert(R);
    while (head != tail) {
        tNode=Delete();
        printf("%d ",tNode->data);
        if (tNode->left) Insert(tNode->left);
        if (tNode->right) Insert(tNode->right);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
         Node *Left,*Right;
 
    InitQueue(128);
    InitTree(1);
    Left=AddChild(Root,2,true);
    Right=AddChild(Root,3,false);
    AddChild(Left,4,true);
    AddChild(Left,5,false);
    AddChild(Right,6,true);
 
    LevelOrder(Root);puts("");
 
    FreeTree(Root);
    FreeQueue();

    system("pause");
    return 0;
}