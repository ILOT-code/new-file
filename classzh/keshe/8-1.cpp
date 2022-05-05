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
using namespace std;
typedef  int  Status;


typedef  struct  BiTNode {
	int        data;
	struct  BiTNode  *lchild, *rchild;
} BiTNode,  *BiTree;

void  CreateBiTree(BiTree  &T)
{        int  ch;
        scanf("%d",&ch);
        if  (ch  ==  -1)  T  =  NULL;
        else
        {        T  =  (BiTNode  *)malloc(sizeof(BiTNode));
                T->data  =  ch;
                CreateBiTree(T->lchild);
                CreateBiTree(T->rchild);
        }
}

void  IsBST(BiTree  T, BiTree  &pre, int  &isBST){
	if(T == NULL) return;
	IsBST(T->lchild,pre,isBST);
	if(pre != NULL && T->data < pre->data) isBST = 0;
	pre = T;
	IsBST(T->rchild,pre,isBST);
}

int  main()
{        BiTree  T,pre=NULL;
                int  isBST  =  TRUE;
//        printf("请输入先序序列创建二叉树：");

        CreateBiTree(T);
        
        IsBST(T,pre,isBST);
        if(isBST)
                printf("是");
        else
                printf("不是");

        printf("\n");
        return  1;  
}