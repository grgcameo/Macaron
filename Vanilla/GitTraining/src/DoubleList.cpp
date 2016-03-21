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

Node* InsertNodeRight(Node *Target, Node *aNode)
{

}

Node* InsertNodeLeft(Node *Target, Node *aNode)
{

}

void UnInitList()
{
    free(head);
}


int _tmain(int argc, _TCHAR* argv[])
{

    system("pause");
    return 0;
}
