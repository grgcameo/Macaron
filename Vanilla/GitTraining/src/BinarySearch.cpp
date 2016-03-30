#include "stdafx.h"
#include <iostream>

int BinarySearch(int *ar, unsigned num, int key)
{
    unsigned Upper, Lower, Mid;

    Lower = 0;
    Upper = num - 1;
    
    for(;;)
    {
        Mid = (Upper + Lower) / 2;

        if (ar[Mid] == key)
        {
            return Mid;
        }
        else
        {
            if (ar[Mid] > key)
            {
                Upper = Mid - 1;
            }
            else
            {
                Lower = Mid + 1;
            }
        }

        if (Upper <= Lower)
        {
            return -1;
        }
    }
}

int compare(const void *elem1,const void *elem2)
{
    // �ܼ��� ���� ���� ���� ���൵ �ǰ�.. ���, ����, 0�� �� �����ؼ� �����ϸ� �Ǵµ�

     //return (*(int *)elem1 - *(int *)elem2);    

    if (*(int *)elem1 > *(int *)elem2)
        return 1;
    else if (*(int *)elem1 < *(int *)elem2)
        return -1;
    else
        return 0;
    
}

int _tmain(int argc, _TCHAR* argv[])
{
    int ar[]={2,6,13,19,21,21,23,29,35,48,62,89,90,95,99,102,109,208,629};
    unsigned num;
    int key,idx;
    int *ptr;

    num=sizeof(ar)/sizeof(ar[0]);
    key=29;
    
    // 1. ����� ����
    idx=BinarySearch(ar,num,key);
    if (idx == -1) {
        puts("ã�� ���� �����ϴ�.");
    } else {
        printf("ã�� ���� %d��°�� �ֽ��ϴ�.\n",idx);
    }

    // ǥ���Լ� ���
    ptr=(int *)bsearch(&key,ar,num,sizeof(int),compare);
    if (ptr==NULL) {
        puts("[bsearch]ã�� ���� �����ϴ�.");
    } else {
        printf("[bsearch]ã�� ���� %d��°�� �ֽ��ϴ�.\n",ptr-ar);
    }

    system("pause");
    return 0;
}