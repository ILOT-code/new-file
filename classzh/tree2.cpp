#include<cstdio>
#include<algorithm>
using namespace std;
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
int deepth(BiTree T){
    if(T==NULL) return 0;
    return 1+min(deepth(T->lchild),deepth(T->rchild));
}
int main(){
    BiTNode a,b,c,d;
    a.data=1;b.data=2;c.data=3;d.data=4;
    a.lchild=&b; a.rchild=&c;
    b.lchild=b.rchild=NULL;
    c.lchild=NULL;
    c.rchild=&d;
    d.lchild=d.rchild=NULL;
    int n=deepth(&a);
    printf("%d\n",n);
    return 0;
}