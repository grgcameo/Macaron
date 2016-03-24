#include "stdafx.h"
#include "Turboc.h"
#include <iostream>


int *Queue;
int QSize;
int head, tail;

void InitQueue(int size)
{
    QSize = size;
    Queue = (int*)malloc(QSize * sizeof(int));
    head = 0;
    tail = 0;
}
void FreeQueue()
{
    free(Queue);
    Queue = NULL;
}

bool Insert(int data)
{
    if ((tail + 1) % QSize == head)
        return false;

    Queue[tail] = data;
    tail = (tail + 1) % QSize;

    return true;
}

int Delete()
{
    int data;

    if (head == tail)
        return -1;

    data = Queue[head];
    head = (head + 1) % QSize;

    return data;
}

void PrintQueue()
{
    int num;
    int x,y;

    num = tail - head;

    // ���� ť�̱⶧���� head�� tail���� �ε��� ���ڰ� Ŭ �� ����
    if (num < 0)
        num += QSize;

    x = wherex();
    y = wherey();

    gotoxy(0, 0);
    printf("��� ���� ���� �� : %d", num);
    gotoxy(x, y);
}

int _tmain(int argc, _TCHAR* argv[])
{
    int doc = -1;
    int num;

    randomize();
    InitQueue(128);

    puts("�μ����� ...");

    for (;;)
    {
        if (_kbhit())
        {
            if (_getch() == ' ')
                break;
        }

        // 5�ʿ� �� ���� ������ ���´�. ������ ���� 2~10������
        if (random(5) == 0)
        {
            num = random(9) + 2;

            if (Insert(num) == true)
            {
                printf("%d ������¥�� �� ���� ���� ��\n", num);
                PrintQueue();
            }
            else
            {
                puts("ť�� ���� ���� ���� �Ұ�");
            }
        }

        if (doc == -1)
        {
            doc = Delete();
            if (doc != -1)
            {
                clrscr();
                PrintQueue();
                gotoxy(0, 5);
                printf("%d ������¥�� ���� �μ� ����\n",doc);                   
            }
        }
        else
        {
            printf("%d ������ �μ���...\n",doc);
            
            if (doc==1)
            {
                doc=-1;
            }
            else
            {
                doc--;
            }
        }
        delay(1000);
    }
    FreeQueue();
    system("pause");
    return 0;
}