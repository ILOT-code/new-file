typedef  struct  BiTNode{
        int        data;
        struct  BiTNode  *lchild,*rchild;
}BiTNode,  *BiTree;

typedef  int  VertexType;
VertexType  Path[20];
void  Solution(BiTree  T,int  targetSum){
	static int cnt = 0;
	static int sum = 0;
	if(T == NULL) return;
	Path[cnt++] = T->data;
	sum += T->data;
	if(sum > targetSum && !(T->lchild == NULL && T->rchild == NULL)){
		cnt--;
		sum -= T->data;
		return;
	}  //剪枝
	if(sum == targetSum && T->lchild == NULL && T->rchild == NULL){
		for(int i = 0; i < cnt; ++i) printf("%d ", Path[i]);
		printf("\n");
	}
	Solution(T->lchild,targetSum);
	Solution(T->rchild,targetSum);
	cnt--;
	sum -= T->data;
}