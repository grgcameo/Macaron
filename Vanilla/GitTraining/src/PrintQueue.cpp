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

    // 원형 큐이기때문에 head가 tail보다 인덱스 숫자가 클 수 있음
    if (num < 0)
        num += QSize;

    x = wherex();
    y = wherey();

    gotoxy(0, 0);
    printf("대기 중인 문서 수 : %d", num);
    gotoxy(x, y);
}

int _tmain(int argc, _TCHAR* argv[])
{
    int doc = -1;
    int num;

    randomize();
    InitQueue(128);

    puts("인쇄대기중 ...");

    for (;;)
    {
        if (_kbhit())
        {
            if (_getch() == ' ')
                break;
        }

        // 5초에 한 번씩 문서가 들어온다. 페이지 수는 2~10페이지
        if (random(5) == 0)
        {
            num = random(9) + 2;

            if (Insert(num) == true)
            {
                printf("%d 페이지짜리 새 문서 삽입 됨\n", num);
                PrintQueue();
            }
            else
            {
                puts("큐가 가득 차서 삽입 불가");
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
                printf("%d 페이지짜리 문서 인쇄 시작\n",doc);                   
            }
        }
        else
        {
            printf("%d 페이지 인쇄중...\n",doc);
            
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