#include "stdafx.h"
#include <iostream>

// 노드 구조체
struct Node
{
    int value;
    Node *next;
};

Node *head;

void InitList()
{
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
}

Node* InsertNode(Node* Target, Node* aNode)
{
    Node *New;

    New = (Node*)malloc(sizeof(Node));
    *New= *aNode;

    New->next = Target->next;
    Target->next = New;

    return New;
}

Node* FindPreNode(Node* CurNode)
{
    // 예외처리 안함
    Node *PreNode;    

    for(PreNode=head->next;PreNode;PreNode=PreNode->next)
    {
        if (PreNode->next == CurNode)
            return PreNode;
    }

    return CurNode;
}

bool DeleteNode(Node *Target)
{
    Node *Del;
    Del = Target->next;
    
    if (Del == NULL)
    {
        return false;
    }

    Target->next = Del->next;

    free(Del);
    return true;
}

void UnInitList()
{
    while(DeleteNode(head))
    {
        ;
    }
    
    free(head);

    head = NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
    int i;
    Node *Now;
    Node Temp;

    InitList();
    Now = head;
    for(i = 1; i <= 5; i++)
    {
        Temp.value = i;
        Now = InsertNode(Now, &Temp);
    }

    DeleteNode(head->next);

    for(Now=head->next;Now;Now=Now->next)
    {
        printf("%d\t", Now->value);
    }
    printf("\n");

    printf("PreNode->value = %d\n", FindPreNode(head->next->next->next->next)->value);

    UnInitList();

    system("pause");

    return 0;
}

