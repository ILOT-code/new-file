//https://uoj.ac/problem/332
//https://www.luogu.com.cn/problem/P3958
#include<cstdio>
using namespace std;
int T,n,pre[1005];
long long h,r;
struct Node
{
    long long x,y,z;
}node[1005];

bool xj(Node a,Node b)
{
    long long d=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
    if(d<=4*r*r) return 1;
    else return 0;
}
int find(int i)
{
    if(pre[i]==i) return i;
    else  return pre[i]=find(pre[i]);
}
void join(int i,int j)
{
    int t=find(i),d=find(j);
    pre[d]=t;
}
int main()
{
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
    {
        scanf("%d %lld %lld",&n,&h,&r);
        for(int i=1;i<=n;i++)
            scanf("%lld %lld %lld",&node[i].x,&node[i].y,&node[i].z);
        for(int i=1;i<=n+2;i++) pre[i]=i;
        for(int i=1;i<=n;i++)
        {
            if(node[i].z+r>=h) join(i,n+1);
            if(node[i].z-r<=0) join(i,n+2);
        }
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
            if(xj(node[i],node[j])) join(i,j);
        if(find(n+1)==find(n+2)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
