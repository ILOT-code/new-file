//https://www.luogu.com.cn/problem/P2483
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 5010;
const int maxm = 200010;
const double inf = 2e9;
int n, m, k, u, v, cur, h[maxn], nxt[maxm], p[maxm], cnt[maxn], ans;
int cur1, h1[maxn], nxt1[maxm], p1[maxm];
double e, ww, w[maxm], f[maxn];
double w1[maxm];
bool tf[maxn];
void add_edge(int x,int y,double z)
{
    cur++;
    nxt[cur]=h[x];
    h[x]=cur;
    p[cur]=y;
    w[cur]=z;
}
void add_edge1(int x,int y,double z)
{
    cur1++;
    nxt1[cur]=h1[x];
    h1[x]=cur1;
    p1[cur]=y;
    w1[cur]=z;
}
struct node
{
    int x;
    double v;
    bool operator<(node a)  const{ return v+f[x]>a.v+f[a.x];}
};
priority_queue<node>q;
struct node1
{
    int x;
    double v;
    bool operator<(node1 a) const{ return v>a.v;}
};
priority_queue<node1>Q;
int main()
{
    scanf("%d%d%lf",&n,&m,&e);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%lf",&u,&v,&ww);
        add_edge(u,v,ww);
        add_edge1(v,u,ww);
    }
    for(int i=1;i<n;++i) f[i]=inf;
    Q.push({n,0});
    while(!Q.empty())
    {
        node1 x=Q.top();
        Q.pop();
        if(tf[x.x]) continue;
        tf[x.x]=1;
        f[x.x]=x.v;
        for(int j=h1[x.x];j;j=nxt1[j]) Q.push({p1[j],w1[j]+x.v});
    }
    k=(int) e/f[1];
    q.push({1,0});
    while(!q.empty())
    {
        node x=q.top();
        q.pop();
        cnt[x.x]++;
        if(x.x==n)
        {
            e-=x.v;
            if(e<0) {printf("%d\n",ans); return 0;}
            ans++;
        }
        for(int j=h[x.x];j;j=nxt[j])
        if(cnt[p[j]]<=k&&x.v+f[x.x]<=e) q.push({p[j],x.v+w[j]});
    }
    printf("%d\n",ans);
    return 0;
}

