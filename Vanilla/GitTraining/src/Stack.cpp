#include "stdafx.h"
#include <iostream>

int *pStack;
int nSize;
int nTop;

void InitStack(int aSize)
{
    nSize = aSize;
    nTop = -1;
    pStack = (int*)malloc(sizeof(int) * nSize);
    memset(pStack, 0, sizeof(int) * nSize);
}

bool Push(int nData)
{
    if (nTop < nSize - 1)
    {   
        pStack[++nTop] = nData;

        return true;
    }
    else
    {
        return false;
    }
}

int Pop()
{
    if (nTop > -1)
    {
        return pStack[nTop--];
    }
    else
    {
        return -1;
    }
}

void FreeStack()
{
    free(pStack);
}

int _tmain(int argc, _TCHAR* argv[])
{
    InitStack(10);

    Push(1);
    Push(2);
    Push(3);
    Push(4);
    Push(5);
    Push(6);

    for (int i = 0; i<10; i++)
    {
        printf("%d", pStack[i]);
    }

    printf("\n");

    printf("%d\n",Pop());
    printf("%d\n",Pop());
    printf("%d\n",Pop());
    printf("%d\n",Pop());
    printf("%d\n",Pop());


    FreeStack();

    system("pause");
    return 0;
}
