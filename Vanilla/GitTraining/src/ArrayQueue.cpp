#include "stdafx.h"
#include <iostream>

int *Queue;
int QSize;
int head, tail;

void InitQueue(int size)
{
    QSize = size;
    head = 0;
    tail = 0;

    Queue = (int*)malloc(QSize * sizeof(int));
}

void FreeQueue()
{
    free(Queue);
    Queue = NULL;
}

bool InsertQueue(int data)
{
    if (((tail + 1) % QSize) == head)
    {
        return false;
    }

    Queue[tail] = data;
    tail = (tail + 1) % QSize;
    
    return true;
}

int Delete()
{
    if (head == tail)
        return -1;

    int data;
    
    data = Queue[head];
    head = (head + 1) % QSize;

    return data;
}


int _tmain(int argc, _TCHAR* argv[])
{
    int i;

    InitQueue(10);
    printf("빈 상태에서 삭제할 때 = %d\n",Delete());
    for (i=0;i<9;i++)
    {
        InsertQueue(i);
    }

     printf("가득찬 상태에서 삽입 %s\n",InsertQueue(100) ? "성공":"실패");
    
     for (i=0;i<9;i++)
     {
          printf("%d  ",Delete());
     }

    FreeQueue();
    system("pause");
    return 0;
}