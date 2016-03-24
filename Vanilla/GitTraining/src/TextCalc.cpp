#include "stdafx.h"
#include <iostream>

// character stack
char *cStack;
int cSize;
int cTop;

void cInitStack(int aSize)
{
    cSize = aSize;
    cTop = -1;
    cStack = (char*)malloc(cSize * sizeof(char));
}

void cFreeStack()
{
    free(cStack);
}

bool cPush(char data)
{
    if (cTop < cSize -1)
    {
        cStack[++cTop] = data;;

        return true;
    }
    else
    {
        return false;
    }
}

char cPop()
{
    if (cTop > -1)
    {
        return cStack[cTop--];
    }
    else
    {
        return -1;
    }

}

double *dStack;
int dSize;
int dTop;

void dInitStack(int aSize)
{
    dSize = aSize;
    dTop = -1;
    dStack = (double*)malloc(dSize * sizeof(double));
}

void dFreeStack()
{
    free(dStack);
}

bool dPush(double data)
{
    if (dTop < dSize - 1)
    {
        dStack[++dTop] = data;

        return true;
    }
    else
    {
        return false;
    }
}

double dPop()
{
    if (dTop > -1)
    {
        return dStack[dTop--];
    }
    else
    {
        return -1;
    }
}

int GetPriority(int op)
{
    switch(op)
    {
    case '(':
        return 0;
        
    case '+':
    case '-':
        return 1;
        
    case '*':
    case '/':
        return 2;

    case '^':
        return 3;

    default :
        return 100;
    }
}

void MakePostfix(char *Post, const char *Mid)
{
     const char *m=Mid;
     char *p=Post,c;
     cInitStack(256);
 
     while (*m) 
     {
          // 숫자 - 그대로 출력하고 뒤에 공백 하나를 출력한다.
          if (isdigit(*m))
          {
              while (isdigit(*m) || *m=='.')
                  *p++=*m++;

              *p++=' ';
          }
          else if (strchr("^*/+-",*m))
          {
            // 연산자는 스택에서 두 수를 꺼내 연산하고 다시 푸시한다.
              while (cTop!=-1 && GetPriority(cStack[cTop]) >= GetPriority(*m))
              {
                   *p++=cPop();
              }

              cPush(*m++);

          }
          else if (*m=='(') 
          {
            // 여는 괄호 - 푸시한다.
              cPush(*m++);
          } 
          else if (*m==')') 
          {
            // 닫는 괄호 - 여는 괄호가 나올 때까지 팝해서 출력하고 여는 괄호는 버린다.
              for (;;) {
                   c=cPop();
                   if (c=='(') break;
                   *p++=c;
               }
              m++;
          } 
          else
          {
              m++;
          }
     }
     // 스택에 남은 연산자들 모두 꺼낸다.
     while (cTop != -1)
     {
          *p++=cPop();
     }
     *p=0;
     cFreeStack();
}
 
double CalcPostfix(const char *Post)
{
     const char *p=Post;
     double num;
     double left,right;
 
     dInitStack(256);
     while (*p) {
          // 숫자는 스택에 넣는다.
          if (isdigit(*p)) {
              num=atof(p);
              dPush(num);
              for(;isdigit(*p) || *p=='.';p++) {;}
          } else {
              // 연산자는 스택에서 두 수를 꺼내 연산하고 다시 푸시한다.
              if (strchr("^*/+-",*p)) {
                   right=dPop();
                   left=dPop();
                   switch (*p) {
                   case '+':
                        dPush(left+right);
                        break;
                   case '-':
                        dPush(left-right);
                        break;
                   case '*':
                        dPush(left*right);
                        break;
                   case '/':
                        if (right == 0.0) {
                             dPush(0.0);
                        } else {
                             dPush(left/right);
                        }
                        break;
                   case '^':
                        dPush(pow(left,right));
                        break;
                   }
              }
              // 연산 후 또는 연산자가 아닌 경우 다음 문자로
              p++;
          }
     }
     if (dTop != -1) {
          num=dPop();
     } else {
          num=0.0;
     }
     dFreeStack();
     return num;
}
 
double CalcExp(const char *exp,bool *bError=NULL)
{
     char Post[256];
     const char *p;
     int count;
    
     if (bError!=NULL) {
          for (p=exp,count=0;*p;p++) {
              if (*p=='(') count++;
              if (*p==')') count--;
          }
          *bError=(count != 0);
     }
 
     MakePostfix(Post,exp);
     return CalcPostfix(Post);
}


int _tmain(int argc, _TCHAR* argv[])
{
     char exp[256];
     bool bError;
     double result;
 
     char *p=strchr((char*)"^*/+-",NULL);
     strcpy(exp,"2.2+3.5*4.1");printf("%s = %.2f\n",exp,CalcExp(exp));
     strcpy(exp,"(34+93)*2-(43/2)");printf("%s = %.2f\n",exp,CalcExp(exp));
     strcpy(exp,"1+(2+3)/4*5+2^10+(6/7)*8");printf("%s = %.2f\n",exp,CalcExp(exp));
 
     for (;;) {
          printf("수식을 입력하세요(끝낼 때 0) : ");
          gets(exp);
          if (strcmp(exp,"0")==0) break;
          result=CalcExp(exp,&bError);
          if (bError) {
              puts("수식의 괄호짝이 틀립니다.");
          } else {
              printf("%s = %.2f\n",exp,result);
          }
     }

    system("pause");
    return 0;
}