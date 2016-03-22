#include "stdafx.h"
#include <iostream>
#include <conio.h>

struct tag_NameCard
{
    char name[10];
    char tel[15];
    char addr[32];
    tag_NameCard *prev;
    tag_NameCard *next;
};

#define ELETYPE tag_NameCard
ELETYPE *head;

void InitList()
{
    head = (ELETYPE*)malloc(sizeof(ELETYPE));
    head->prev = NULL;
    head->next = NULL;
}

ELETYPE* FindNodeByName(char *DelName)
{
    ELETYPE *Find;

    for (Find=head->next;Find;Find=Find->next)
    {
        if (strcmp((const char*)Find->name, (const char*)DelName) == 0)
            return Find;
    }

    return NULL;
}

int GetNodeIndex(ELETYPE *Target)
{
    int index = 0;
    ELETYPE *Find;

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
    ELETYPE *Now;
    int Count = 0;

    for (Now=head->next;Now;Now=Now->next)
    {
        Count++;
    }

    return Count;
}

ELETYPE* InsertNodeRight(ELETYPE *Target, ELETYPE *aNode)
{
    ELETYPE *New;
    ELETYPE *Right;

    New = (ELETYPE*)malloc(sizeof(ELETYPE));
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

ELETYPE* InsertNodeLeft(ELETYPE *Target, ELETYPE *aNode)
{
#if 1
    ELETYPE *Left;
    Left = Target->prev;

    if (Left)
    {
        return InsertNodeRight(Left, aNode);
    }

    return NULL;
#else
    ELETYPE *New;
    ELETYPE *Left;

    New = (ELETYPE*)malloc(sizeof(ELETYPE));
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

void AppendNode(ELETYPE* aNode)
{
    ELETYPE *tail;

    for (tail=head;tail->next; tail=tail->next)
    {
        ;
    }

    InsertNodeRight(tail, aNode);

}

bool DeleteNode(ELETYPE *Target)
{
    if (Target == NULL || Target == head)
    {
        return false;
    }

    ELETYPE *Left;
    ELETYPE * Right;
 
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
    char ch;
    ELETYPE Temp;

    InitList();

    while(true) 
    {
        printf("����� �Է��ϼ���.(1:����, 2:�߰�, 3:����, Q:����) >");
        ch = _getch();
        printf("\n");
        
        if (ch == 'Q' || ch == 'q')
        {
            break;
        }

        switch(ch)
        {
        case '1':
            if (GetListCount() == 0)
            {
                printf("��ϵ� ������ �����ϴ�.\n");
            }
            else
            {
                ELETYPE *Now;
                for (Now=head->next;Now;Now=Now->next)
                {
                    printf("#####################################\n");
                    printf("[�̸�]    : %s\n", Now->name);
                    printf("[��ȭ��ȣ]: %s\n", Now->tel);
                    printf("[�ּ�]    : %s\n", Now->addr);
                    printf("#####################################\n");
                }
            }
            break;

        case '2':
            printf("�̸��� �Է��ϼ���(9��) : ");gets(Temp.name);
            printf("��ȭ��ȣ�� �Է��ϼ���(14��) : ");gets(Temp.tel);
            printf("�ּҸ� �Է��ϼ���(32��) : ");gets(Temp.addr);
            AppendNode(&Temp);
            break;

        case '3':
            printf("������ �̸��� �Է��ϼ��� :");gets(Temp.name);
            ELETYPE *Del;
            Del = FindNodeByName(Temp.name);
            if (Del != NULL)
            {
                DeleteNode(Del);
            }
            else
            {
                printf("��ϵ��� ���� �̸��Դϴ�.\n");
            }
            break;
        }
    }

    UnInitList();

    system("pause");

	return 0;
}

