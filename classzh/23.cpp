#include<stdio.h>
#include<stdlib.h>
using namespace std;
int n;
typedef struct node
{
	int data;
	struct node *next;
}LNode,*LinkList;
int main(){
    printf("请输入该循环链表的长度：\n");
    scanf("%d",&n);
    LinkList head,p;
	head=(LinkList)malloc(sizeof(LNode));
	head->next=head;
    for(int i=1;i<=n;++i){
        p=(LinkList)malloc(sizeof(LNode));
        scanf("%d",&p->data);
	    p->next=head->next;
	    head->next=p;
    }
    p=head;
    while(p->next!=head){
        p=p->next;
        printf("%d ",p->data);
    }
    return 0;
}