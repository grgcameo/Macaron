#include "stdafx.h"
#include <iostream>

int LinearSearch(int *ar, unsigned num, int key)
{
    unsigned i;

    for (i = 0; i < num; i++)
    {
        if (ar[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    int ar[]={23,47,19,63,57,26,75,73,82,89,47,11};
    unsigned num;
    int key, idx;

    num = sizeof(ar) / sizeof(ar[0]);
    key = 75;

    idx = LinearSearch(ar, num, key);

    if (idx == -1)
    {
        puts("ã�� ���� �����ϴ�.");
    }
    else
    {
        printf("ã�� ���� %d��°�� �ֽ��ϴ�.\n",idx);
    }

    system("pause");
    return 0;
}