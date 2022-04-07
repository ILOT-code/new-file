#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=1000+5;
int n;
int in_order[maxn],post_order[maxn],lch[maxn],rch[maxn];
bool read_list(int *a){
    string line;
    if(!getline(cin,line))  return false;
    stringstream ss(line);
    n=0;
    int x;
    while(ss>>x)  a[n++]=x;
    return n>0;
}
int build(int L1,int R1,int L2,int R2){
    if(L1>R1)  return 0;
    int root=post_order[R2];
    int pos;
    for(pos=L1;pos<=R1;pos++)
        if(in_order[pos]==root)  break;
    int cnt=pos-L1;
    lch[root]=build(L1,pos-1,L2,L2+cnt-1);
    rch[root]=build(pos+1,R1,L2+cnt,R2-1);
    return root;
}
int ans,v;
void dfs(int root,int sum){
    sum+=root;
    if(!rch[root]&&!lch[root])
        if(sum<ans)  {ans=sum; v=root;}
        else if(sum==ans)  v=min(v,root);
    if(lch[root])  dfs(lch[root],sum);
    if(rch[root])  dfs(rch[root],sum);
}
int main(){
    while(read_list(in_order)){
        read_list(post_order);
        build(0,n-1,0,n-1);
        ans=10000000;
        dfs(post_order[n-1],0);
        cout<<v<<endl;
    }
    return 0;
}