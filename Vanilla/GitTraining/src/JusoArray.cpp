// JusoArray.cpp : 동적 배열 활용
//

#include "stdafx.h"
#include <iostream>

struct tag_NameCard
{
    char name[10];
    char tel[15];
    char addr[32];
};

#define ELETYPE tag_NameCard
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
    char ch;
    unsigned i;
    tag_NameCard Temp;

    InitArray(10,5);

    while(true) 
    {
        printf("명령을 입력하세요.(1:보기, 2:추가, 3:삭제, Q:종료) >");
        ch = getchar();
        printf("\n");
        
        if (ch == 'Q' || ch == 'q')
        {
            break;
        }

        switch(ch)
        {
        case '1':
            if (num == 0)
            {
                printf("등록된 내용이 없습니다.\n");
            }
            else
            {
                for (i = 0; i < num; i++)
                {
                    printf("%d, 이름:%s, 전화:%s, 주소:%s\n",i,ar[i].name, ar[i].tel,ar[i].addr);
                }
            }

            break;

        case '2':
            printf("이름을 입력하세요(9자) : ");gets(Temp.name);
            printf("전화번호를 입력하세요(14자) : ");gets(Temp.tel);
            printf("주소를 입력하세요(32자) : ");gets(Temp.addr);
            Append(Temp);
            break;

        case '3':
            printf("삭제할 번호를 입력하세요 :");scanf_s("%d", &i);
            if (i < num)
            {
                Delete(i);
            }
            else
            {
                printf("등록되지 않은 변호입니다.\n");
            }
            break;
        }
    }

    UnInitArray();

    system("pause");

	return 0;
}

