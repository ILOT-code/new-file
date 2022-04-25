#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <assert.h>
#include  <stddef.h>
#define  TRUE  1
#define  FALSE  0
#define  OK  1
#define  ERROR  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
#define  LIST_INIT_SIZE  100
#define  STACK_INIT_SIZE  100
typedef  int  Status;

typedef  struct  {
        int  *base;
        int  *top;
        int  stacksize;
} Stack;

Status  InitStack(Stack  &S)
{
        S.base  =  (int  *)malloc(STACK_INIT_SIZE  *  sizeof(int));
        if (!S.base)  exit(OVERFLOW);
        S.stacksize  =  STACK_INIT_SIZE;
        S.top  =  S.base;
        return  OK;
}//InitStack

Status  GetTop(Stack  S, int  &e)
{       if  (S.top == S.base)  return  ERROR;
        e  =  *(S.top - 1);
        return  OK;
}

Status  Push(Stack  &S,  int  x)
{
        if (S.top  -  S.base    >=  S.stacksize  )  return  OVERFLOW;
        *S.top++  =  x;
        return  OK;
}//push

Status  Pop(Stack  &S,  int  &x)
{
        if (S.top  ==  S.base  )  return  ERROR;
        x  =  *(--S.top);
        return  OK;
}//pop

Status  StackEmpty(Stack  S)
{
        if (S.top  ==  S.base  )  return  TRUE;
        else  return  FALSE;
}

//形参分别为存行星的整型数组，数组大小
int          asteroidCollision(int*  asteroids,  int  asteroidsSize) {
        Stack  leftStack, rightStack;
        int  e;
        InitStack(leftStack);//存左行星，他左侧没有右行星
        InitStack(rightStack);//存右行星，等待左行星到来
        Stack ans;
        InitStack(ans);
        for (int i = 0; i < asteroidsSize; ++i) {
                if (asteroids[i] > 0)  Push(ans, asteroids[i]);
                else {
                        bool flag = 1;
                        while (!StackEmpty(ans) && (GetTop(ans, e), e) > 0) {
                                if (e > -asteroids[i]) {
                                        flag = 0;
                                        break;
                                }
                                if (e < -asteroids[i])
                                        Pop(ans, e);
                                else {
                                        flag = 0;
                                        Pop(ans, e);
                                        break;
                                }
                        }
                        if (flag) Push(ans, asteroids[i]);
                }
        }
        for(int *i =ans.base; i < ans.top; ++i)
                printf("%d ",*i);

}

int  main(int  argc,  char**  argv)
{
        int  nums[100];
        for (int  i = 1;  i < argc;  i++)
                nums[i - 1]  =  atoi(argv[i]);
        asteroidCollision(nums, argc - 1);
        return  OK;
}