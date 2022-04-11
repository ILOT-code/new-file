#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef struct BiTNode{
char s; //该结点的字母
int value; //权值
int deep=0; //编码长度
int a[10]; //编码数组
struct BiTNode *lchild, *rchild; //左右孩子
BiTNode(char s=0,int
value=0):s(s),value(value),lchild(NULL),rchild(NULL){}; //编写初始化函数
bool operator<(const BiTNode &a){ //定义运算符
return value<a.value;
}
}BiTNode, *BiTree;
void add(BiTree T,int n){ //为树T的树叶增加编码
if(T->lchild==NULL&&T->rchild==NULL) T->a[(T->deep)++]=n;
if(T->lchild!=NULL) add(T->lchild,n);
if(T->rchild!=NULL) add(T->rchild,n);
} B
iTree link(BiTree a,BiTree b){ //连接两棵树
BiTree root=(BiTree)malloc(sizeof(BiTNode));
root->lchild=a;
root->rchild=b;
root->value=a->value+b->value;
add(a,0);
add(b,1);
return root;
} v
oid solve(BiTree a){ //解决函数
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
} i
nt main(){