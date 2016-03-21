// DynArray.cpp : 동적 배열 테스트
//

#include "stdafx.h"
#include <iostream>

#define ELETYPE int
ELETYPE *ar;
unsigned size;  // 할단된 배열의 크기
unsigned num;   // 배열에 삽입된 개수  
unsigned growby;// 배열 확장 시 여유분의 크기

void InitArray(unsigned asize, unsigned agrowby)
{
    size = asize;
    growby = agrowby;
    num = 0;
    ar = (ELETYPE*)malloc(size*sizeof(ELETYPE));
}

void Insert(int idx, ELETYPE value)
{
    unsigned need;

    need = num + 1; // 현재 삽입된 배열의 + 1 이 필요한 배열의 크기
    
    if (need > size) 
    {   // 할당된 배열의 크기보다 필요한 배열의 크기가 더 클때 배열을 확장한다.
        size = need + growby; // 필요한 크기 + 여유분 크기
        ar = (ELETYPE*)realloc(ar, size*sizeof(ELETYPE)); // 메모리 재할당
    }
    
    memmove(ar+idx+1, ar+idx, (num-idx)*sizeof(ELETYPE));
    ar[idx] = value;
    num++;
}

void Delete(int idx)
{
    memmove(ar+idx, ar+idx+1, (num-idx-1)*sizeof(ELETYPE));
    num--;
}

void Append(ELETYPE value)
{
    Insert(num, value);
}

void UnInitArray()
{
    free(ar);
}

void DumpArray(char *sMark)
{
    unsigned i;

    printf("%16s => 크기=%02d, 개수=%02d : ", sMark, size, num);

    for(int i = 0; i < num; i++)
    {
        printf("%2d ", ar[i]);
    }
    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{    
    int i;
 
    InitArray(10,5);DumpArray("최초");

    for (i=1;i<=8;i++) 
        Append(i);
    
    DumpArray("8개 추가");
    
    Insert(3,10);DumpArray("10 삽입");
    Insert(3,11);DumpArray("11 삽입");
    Insert(3,12);DumpArray("12 삽입");
    
    Delete(7);DumpArray("요소 7 삭제");
 
    UnInitArray();

    system("pause");

	return 0;
}

