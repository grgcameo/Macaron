#include "stdafx.h"
#include <iostream>

// character stack
char *cStack;
int cSize;
int cTop;

void cInitStack(int aSize)
{
    cSize = aSize;
    cTop = -1;
    cStack = (char*)malloc(cSize * sizeof(char));
}

void cFreeStack()
{
    free(cStack);
}

bool cPush(char data)
{
    if (cTop < cSize -1)
    {
        cStack[++cTop] = data;;

        return true;
    }
    else
    {
        return false;
    }
}

char cPop()
{
    if (cTop > -1)
    {
        return cStack[cTop--];
    }
    else
    {
        return -1;
    }

}

double *dStack;
int dSize;
int dTop;

void dInitStack(int aSize)
{
    dSize = aSize;
    dTop = -1;
    dStack = (double*)malloc(dSize * sizeof(double));
}

void dFreeStack()
{
    free(dStack);
}

bool dPush(double data)
{
    if (dTop < dSize - 1)
    {
        dStack[++dTop] = data;

        return true;
    }
    else
    {
        return false;
    }
}

double dPop()
{
    if (dTop > -1)
    {
        return dStack[dTop--];
    }
    else
    {
        return -1;
    }
}

int GetPriority(int op)
{
    switch(op)
    {
    case '(':
        return 0;
        
    case '+':
    case '-':
        return 1;
        
    case '*':
    case '/':
        return 2;

    case '^':
        return 3;

    default :
        return 100;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{

    system("pause");
    return 0;
}