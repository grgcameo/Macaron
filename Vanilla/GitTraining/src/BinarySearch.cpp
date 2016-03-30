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
    // 단순히 값의 차로 전달 해줘도 되고.. 양수, 음수, 0만 잘 정리해서 리턴하면 되는듯

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
    
    // 1. 사용자 정의
    idx=BinarySearch(ar,num,key);
    if (idx == -1) {
        puts("찾는 값이 없습니다.");
    } else {
        printf("찾는 값은 %d번째에 있습니다.\n",idx);
    }

    // 표준함수 사용
    ptr=(int *)bsearch(&key,ar,num,sizeof(int),compare);
    if (ptr==NULL) {
        puts("[bsearch]찾는 값이 없습니다.");
    } else {
        printf("[bsearch]찾는 값은 %d번째에 있습니다.\n",ptr-ar);
    }

    system("pause");
    return 0;
}