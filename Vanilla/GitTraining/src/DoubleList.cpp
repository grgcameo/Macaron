#include "stdafx.h"
#include <iostream>

struct Node 
{
    int value;
    Node *prev;
    Node *next;
};

Node *head;

void InitList()
{
    head = (Node*)malloc(sizeof(Node));
    head->prev = NULL;
    head->next = NULL;
}

Node* FindNodeByIndex(int idx)
{
    Node *Find;
    int index = 0;

    for (Find=head->next;Find;Find=Find->next)
    {
        if (index == idx)
            return Find;

        index++;
    }

    return NULL;
}

int GetNodeIndex(Node *Target)
{
    int index = 0;
    Node *Find;

    for(Find=head->next;Find;Find=Find->next)
    {
        if (Find == Target)
            return index;
        index++;
    }

    return -1;
}

int GetListCount()
{
    Node *Now;
    int Count = 0;

    for (Now=head->next;Now;Now=Now->next)
    {
        Count++;
    }

    return Count;
}

Node* InsertNodeRight(Node *Target, Node *aNode)
{
    Node *New;
    Node *Right;

    New = (Node*)malloc(sizeof(Node));
    *New = *aNode;
    
    Right = Target->next;
    New->prev = Target;
    New->next = Right;
    Target->next = New;
    
    if(Right)
    {
        Right->prev = New;
    }

    return New;
}

Node* InsertNodeLeft(Node *Target, Node *aNode)
{
#if 1
    Node *Left;
    Left = Target->prev;

    if (Left)
    {
        return InsertNodeRight(Left, aNode);
    }

    return NULL;
#else
    Node *New;
    Node *Left;

    New = (Node*)malloc(sizeof(Node));
    *New = *aNode;

    Left = Target->prev;
    New->next = Target;
    New->prev = Left;
    Target->prev = New;

    if (Left)
    {
        Left->next = New;
    }

    return New;

#endif
}

void AppendNode(Node* aNode)
{
    Node *tail;

    for (tail=head;tail->next; tail=tail->next)
    {
        ;
    }

    InsertNodeRight(tail, aNode);

}

bool DeleteNode(Node *Target)
{
    if (Target == NULL || Target == head)
    {
        return false;
    }

    Node *Left;
    Node * Right;
 
    Left = Target->prev;
    Right = Target->next;

    Left->next = Right;
    if (Right)
    {
        Right->prev = Left;
    }

    free(Target);

    return true;

}

void UnInitList()
{
    while(DeleteNode(head->next));

    free(head);
    head = NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
    int i;
    Node *Now;
    Node Temp;

    InitList();
    for(i=1;i <= 5;i++)
    {
        Temp.value = i;
        AppendNode(&Temp);
    }

    for(Now=head->next;Now;Now=Now->next)
    {
        printf("%d\t", Now->value);
    }
    printf("\n");

    printf("Node Count : %d\n", GetListCount());
    
    printf("3 Node : %d\n", FindNodeByIndex(3)->value);

    UnInitList();

    system("pause");
    return 0;
}
