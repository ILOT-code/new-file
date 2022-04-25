typedef  struct  BiTNode {
        int        data;
        struct  BiTNode  *lchild, *rchild;
} BiTNode,  *BiTree;

int  Value(BiTree  root) {
        if (root == NULL) return 0;
        int value1 = root->data; 
        if(root->lchild != NULL) value1 += Value(root->lchild->lchild) + Value(root->lchild->rchild);
        if(root->rchild != NULL) value1 += Value(root->rchild->lchild) + Value(root->rchild->rchild);
        int value2 = Value(root->lchild) + Value(root->rchild);
        return value1 > value2 ? value1 : value2;

}