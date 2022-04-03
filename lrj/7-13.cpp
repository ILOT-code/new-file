//迭代加深搜索
//剪枝策略
//结点先排序
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=2000;
bool vis[maxn];
int a[maxn],mmax;              //a[0]表示长度，mmax表示数列中最大的数；
int n,maxd;
int q_pow(int d){
    if(d==0)    return 1;
    return 2*q_pow(d-1);
}
bool dfs(int d){
    if(mmax*q_pow(maxd-d)<n)  return false;
    if(d==maxd){
        if(vis[n])  return true;
        else        return false;
    }
    vector<int> q;
    int b_mmax=mmax;
    for(int i=a[0];i>0;--i){
        for(int j=i;j>0;--j){
            int temp=a[i]+a[j];
            if(vis[temp]) continue;
            for(int k=0;k<q.size();++k)
                if(temp==q[k]) continue;
            vis[temp]=1;
            q.push_back(temp);
            a[0]++;
            a[a[0]]=temp;
            for(int i=1;i<=a[0];++i)
                mmax=max(mmax,a[i]);
            if(dfs(d+1))    return true;
            a[a[0]]=0;
            a[0]--;
            vis[temp]=0;
            mmax=b_mmax;
        }
    }
    for(int i=a[0];i>0;--i){
        for(int j=1;j<i;++j){
            int temp=a[i]-a[j];
            if(vis[temp])   continue;
            for(int k=0;k<q.size();++k)
                if(temp==q[k])  continue;
            vis[temp]=1;
            q.push_back(temp);
            a[0]++;
            a[a[0]]=temp;
            if(dfs(d+1))    return true;
            a[a[0]]=0;
            a[0]--;
            vis[temp]=0;
        }
    }
    q.clear();
    return false;
}
int solve(){
    vis[1]=1;a[1]=1;a[0]=1;mmax=1;
    for(maxd=1;;++maxd)
        if(dfs(0))  return maxd;
    return -1;
}
int main(){
    int kase=1;
    while(scanf("%d",&n)){
        memset(vis,0,sizeof(vis));
        memset(a,0,sizeof(a));
        printf("Case:%d %d\n",kase++,solve());
    }
    return 0;
}