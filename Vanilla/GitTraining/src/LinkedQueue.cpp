#include "stdafx.h"
#include <iostream>


struct Node
{
    int value;
    Node *prev;
    Node *next;
};

Node *head;

void InitQueue()
{
    head = (Node*)malloc(sizeof(Node));
    head->prev = NULL;
    head->next = NULL;
}

void InsertQueue(int data)
{
    Node *New;
    Node *tail;

    for (tail=head;tail->next;tail=tail->next)
    {
        ;
    }

    New = (Node*)malloc(sizeof(Node));
    New->value = data;

    New->next = NULL;
    New->prev = tail;
    tail->next = New;
}

int Delete()
{
    int data;
    Node *Target;

    Target = head->next;

    if (Target == NULL)
    {
        return -1;
    }

    data = Target->value;
    head->next = Target->next;

    if (head->next)
    {
        head->next->prev = head;
    }

    free(Target);

    return data;
}

void FreeQueue()
{
    while(Delete() != -1)
    {
        ;
    }

    free(head);
    head = NULL;
}
        
int _tmain(int argc, _TCHAR* argv[])
{
    int i;

    InitQueue();

    for (i = 0;i < 100;i++)
    {
        InsertQueue(i);
    }

    for (i = 0;i < 100;i++)
    {
        printf("%d    ", Delete());
    }

    FreeQueue();

    system("pause");
    return 0;
}