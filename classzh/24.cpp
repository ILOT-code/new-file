#include<stdio.h>
#include<stdlib.h>
using namespace std;
int n,mink,maxk;
typedef struct node
{
	int data;
	struct node *next;
}LNode,*LinkList;
void input(LinkList P,int t){
    if(!t) return;
    LinkList pp=(LinkList)malloc(sizeof(LNode));
    scanf("%d",&(pp->data));
    P->next=pp;
    pp->next=NULL;
    input(pp,--t);
}
void output(LinkList P){
    while(P->next!=NULL){
        P=P->next;
        printf("%d",P->data);
    }
}
void dele(LinkList P){
    while(P->next!=NULL&&P->next->data<mink)  {P=P->next;}
    if(P->next==NULL)       {return;}
    LinkList PL=P;
    while(P->next!=NULL&&P->next->data<=maxk)  {P=P->next;}
    LinkList PR=P->next;
    PL->next=PR;
}
int main(){
    printf("请输入该循环链表的长度：\n");
    scanf("%d",&n);
    LinkList head;
	head=(LinkList)malloc(sizeof(LNode));
    head->next=NULL;
    input(head,n);
    printf("请输入mink与maxk的值:\n");
    scanf("%d%d",&mink,&maxk);
    dele(head);
    output(head);
    return 0;
}