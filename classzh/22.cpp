#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
int T,sum,x;                                     //T为项数，sum为结果，x是变量；
typedef struct node                              //定义该一元多项式
{
	int coef,expo;
	struct node *next;
}LNode,*LinkList;
void input(int t,LinkList P){                     //输入函数
    if(!t)  return;
    LinkList P1=(LinkList)malloc(sizeof(LNode));
    printf("请输入第%d项的系数:\n",T-t+1);
    scanf("%d",&(P1->coef));
    printf("请输入第%d项的指数:\n",T-t+1);
    scanf("%d",&(P1->expo));
    P->next=P1;
    P1->next=NULL;
    input(--t,P1);
}  
void solve(LinkList P){                       //求值函数
    if(P->next==NULL) return;
    P=P->next;
    sum+=P->coef*pow(x,P->expo);
    solve(P);
}
int main(){
    LinkList head=(LinkList)malloc(sizeof(LNode));
    head->next=NULL;
    printf("请输入多项式的项数:\n");
    scanf("%d",&T);
    input(T,head);
    printf("请输入变量x的值:\n");
    scanf("%d",&x);
    solve(head);
    printf("值为:%d",sum);
    return 0;
}