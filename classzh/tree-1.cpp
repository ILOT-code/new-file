#include<cstdio>
using namespace std;
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
void preserver(BiTree  T,int  a[], int &n){
    if(T->lchild!=NULL) preserver(T->lchild,a,n);
    a[n--]=T->data;
    if(T->rchild!=NULL) preserver(T->rchild,a,n);
}
int main(){
    BiTNode a,b,c;
    int A[10],n=3;
    a.data=1;b.data=2;c.data=3;
    a.lchild=&b; a.rchild=&c;
    b.lchild=b.rchild=NULL;
    c.lchild=c.rchild=NULL;
    preserver(&a,A,n);
    for(int i=1;i<4;++i)
        printf("%d ",A[i]);
    return 0;
}

