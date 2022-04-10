#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef struct BiTNode{
    char s;
    int value;
    int deep=0;
    int a[10];
    struct BiTNode *lchild, *rchild;
    BiTNode(char s=0,int value=0):s(s),value(value),lchild(NULL),rchild(NULL){};
    bool operator<(const BiTNode &a){
        return value<a.value;
    }
}BiTNode, *BiTree;
void add(BiTree T,int n){
    if(T->lchild==NULL&&T->rchild==NULL) T->a[(T->deep)++]=n;
    if(T->lchild!=NULL) add(T->lchild,n);
    if(T->rchild!=NULL) add(T->rchild,n);
}
BiTree link(BiTree a,BiTree b){
    BiTree root=(BiTree)malloc(sizeof(BiTNode));
    root->lchild=a;
    root->rchild=b;
    root->value=a->value+b->value;
    add(a,0);
    add(b,1);
    return root;
}
void solve(BiTree a){
    queue<BiTree> q;
    int pos=2;
    BiTree u=link(a,a+1);
    q.push(u);
    while(!q.empty()){
        BiTree u1=q.front();
        if(u1->value<a[pos].value) q.pop();
        else u1=&a[pos++];
        if(q.empty()&&pos==8) break;
        BiTree u2=q.front();
        if(u2->value<a[pos].value) q.pop();
        else u2=&a[pos++];
        BiTree u3=link(u1,u2);
        q.push(u3);
    }
}
int main(){
    BiTNode a[9]={{'A',5},{'B',25},{'C',4},{'D',7},{'E',9},{'F',12},{'G',30},{'H',8},{'Z',200}};
    sort(a,a+8);
    solve(a);
    for(int i=0;i<8;++i){
        printf("%c:",a[i].s);
        for(int j=a[i].deep-1;j>=0;--j)
            printf("%d ",a[i].a[j]);
        printf("\n");
    }
    return 0;
}