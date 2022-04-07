#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=1000+5;
struct Node{
    bool have_value;
    int v;
    Node *left,*right;
    Node():have_value(false),left(NULL),right(NULL){}
};

char s[maxn];
Node *root=new Node();
void addnode(int v,char *s){
    int n=strlen(s);
    Node *u=root;
    for(int i=0;i<n;++i){
        if(s[i]=='L'){
            if(u->left==NULL)  u->left=new Node();
            u=u->left;
        }
        if(s[i]=='R'){
            if(u->right==NULL)  u->right=new Node();
            u=u->right;
        }
    }
    u->v=v;
    u->have_value=true;
}
bool read_list(){
    root->have_value=false; root->left=root->right=NULL;
    for(;;){
        if(scanf("%s",s)!=1)  return false;
        if(!strcmp(s,"()"))  break;
        int v;
        sscanf(&s[1],"%d",&v);
        addnode(v,strchr(s,',')+1);
    }
    return true;
}
vector<int> ans;
bool bfs(vector<int>& ans){
    queue<Node*> q;
    ans.clear();
    q.push(root);
    while(!q.empty()){
        Node *u=q.front(); q.pop();
        if(!u->have_value)  return false;
        ans.push_back(u->v);
        if(u->left!=NULL)  q.push(u->left);
        if(u->right!=NULL)  q.push(u->right);
    }
    return true;
}
int main(){
    while(read_list()){
        bfs(ans);
        if(bfs(ans)){
            for(int i=0;i<ans.size();++i)
                printf("%d ",ans[i]);
            printf("\n");
        }
        else  printf("%d",-1);
    }
    return 0;
}