// JusoArray.cpp : ���� �迭 Ȱ��
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
unsigned size;  // �Ҵܵ� �迭�� ũ��
unsigned num;   // �迭�� ���Ե� ����  
unsigned growby;// �迭 Ȯ�� �� �������� ũ��

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

    need = num + 1; // ���� ���Ե� �迭�� + 1 �� �ʿ��� �迭�� ũ��
    
    if (need > size) 
    {   // �Ҵ�� �迭�� ũ�⺸�� �ʿ��� �迭�� ũ�Ⱑ �� Ŭ�� �迭�� Ȯ���Ѵ�.
        size = need + growby; // �ʿ��� ũ�� + ������ ũ��
        ar = (ELETYPE*)realloc(ar, size*sizeof(ELETYPE)); // �޸� ���Ҵ�
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

    printf("%16s => ũ��=%02d, ����=%02d : ", sMark, size, num);

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
        printf("����� �Է��ϼ���.(1:����, 2:�߰�, 3:����, Q:����) >");
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
                printf("��ϵ� ������ �����ϴ�.\n");
            }
            else
            {
                for (i = 0; i < num; i++)
                {
                    printf("%d, �̸�:%s, ��ȭ:%s, �ּ�:%s\n",i,ar[i].name, ar[i].tel,ar[i].addr);
                }
            }

            break;

        case '2':
            printf("�̸��� �Է��ϼ���(9��) : ");gets(Temp.name);
            printf("��ȭ��ȣ�� �Է��ϼ���(14��) : ");gets(Temp.tel);
            printf("�ּҸ� �Է��ϼ���(32��) : ");gets(Temp.addr);
            Append(Temp);
            break;

        case '3':
            printf("������ ��ȣ�� �Է��ϼ��� :");scanf_s("%d", &i);
            if (i < num)
            {
                Delete(i);
            }
            else
            {
                printf("��ϵ��� ���� ��ȣ�Դϴ�.\n");
            }
            break;
        }
    }

    UnInitArray();

    system("pause");

	return 0;
}

