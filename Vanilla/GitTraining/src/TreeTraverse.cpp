#include "stdafx.h"
#include <iostream>

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node *Root;

void InitTree(int data)
{
    Root = (Node*)malloc(sizeof(Node));
    Root->data = data;
}

Node* AddChild(Node *Parent, int data, bool bLeft)
{
    Node *New;

    New = (Node*)malloc(sizeof(Node));
    New->data = data;
    New->left = NULL;
    New->right = NULL;

    if (bLeft)
    {
        Parent->left = New;
    }
    else
    {
        Parent->right = New;
    }
    
    return New;    
}

void PreOrder(Node *R)
{
    printf("%d", R->data);
    
    if (R->left)
        PreOrder(R->left);

    if (R->right)
        PreOrder(R->right);
}

void InOrder(Node *R)
{
    if (R->left)
        InOrder(R->left);

    printf("%d", R->data);
    
    if (R->right)
        InOrder(R->right);
}

void PostOrder(Node *R)
{
    
    
    if (R->left)
        PostOrder(R->left);

    if (R->right)
        PostOrder(R->right);

    printf("%d", R->data);
}

// 생성한 트리를 해제하는 FreeTree 함수는 각 노드를 해제하되 자식 노드를 먼저 해제한 후 루트를 
// 해제해야 하므로 후위 순회법을 사용한다. 
// 루트를 먼저 해제하면 자식 노드를 알 수 없게 되므로 후위 순회가 적합하다.
void FreeTree(Node *R)
{
    if (R->left)
        FreeTree(R->left);
    if (R->right)
        FreeTree(R->right);
    free(R);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Node *Left, *Right;

    InitTree(1);

    Left    = AddChild(Root, 2, true);
    Right   = AddChild(Root, 3, false);

    AddChild(Left, 4, true);
    AddChild(Left, 5, false);
    AddChild(Right, 6, true);

    PreOrder(Root);puts("");
    InOrder(Root);puts("");
    PostOrder(Root);puts("");

    FreeTree(Root);

    system("pause");
    return 0;
}