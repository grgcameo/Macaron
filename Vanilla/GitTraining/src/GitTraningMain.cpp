// GitTraining.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>


char ar[16] = "abcdef";

void Insert(int idx, char ch)
{
    memmove(ar+idx+1, ar+idx, strlen(ar)-idx+1);
    ar[idx]=ch;
}

void Delete(int idx)
{
    memmove(ar+idx, ar+idx+1, strlen(ar)-idx);
}

void Append(char ch)
{
    Insert(strlen(ar), ch);
}

int _tmain(int argc, _TCHAR* argv[])
{
    printf("최초 : %s, ar_len: %d\n", ar, strlen(ar));
    Insert(3, 't');printf("t삽입 : %s, ar_len: %d\n", ar, strlen(ar));
    Delete(1);printf("b삭제 : %s, ar_len: %d\n", ar, strlen(ar));
    Append('s');printf("s추가 : %s, ar_len: %d\n", ar, strlen(ar));

    system("pause");

	return 0;
}

