// GitTraining.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
    printf("���� : %s, ar_len: %d\n", ar, strlen(ar));
    Insert(3, 't');printf("t���� : %s, ar_len: %d\n", ar, strlen(ar));
    Delete(1);printf("b���� : %s, ar_len: %d\n", ar, strlen(ar));
    Append('s');printf("s�߰� : %s, ar_len: %d\n", ar, strlen(ar));

    system("pause");

	return 0;
}

