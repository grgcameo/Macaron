#include "stdafx.h"
#include <iostream>



int _tmain(int argc, _TCHAR* argv[])
{
    typedef union Type{
        char data[4];
        unsigned int cntrl[1];
        char a;
        char b;
        char c;
        char d;
    } test_tag;    

    char tt[1] = {1};
    tt[1] = 3;

    test_tag x;
    x.cntrl[0] = 0x12345678;
    x.cntrl[1] = 0x90abcdef;
    x.data[4] = 1;
    printf("x.cntrl[0] : 0x%x\n\n", x.cntrl[0]);

    printf("x.a : 0x%x\n", x.a);
    printf("x.b : 0x%x\n", x.b);
    printf("x.c : 0x%x\n", x.c);
    printf("x.d : 0x%x\n\n", x.d);
    printf("x.data[0] : 0x%x\n", x.data[0]);
    printf("x.data[1] : 0x%x\n", x.data[1]);
    printf("x.data[2] : 0x%x\n", x.data[2]);
    printf("x.data[3] : 0x%x\n\n", x.data[3]);
    printf("x.data[4] : 0x%x\n\n", x.data[4]);
    
    printf("x.cntrl[1] : 0x%x\n", x.cntrl[1]);

    printf("%d\n", tt[0]);
    printf("%d\n", tt[1]);
    system("pause");
    return 0;
}