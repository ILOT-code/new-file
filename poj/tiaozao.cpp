//http://poj.org/problem?id=1091
#include <iostream>
#include <cstdio>
#define ll long long
using namespace  std;
ll N,M,j=0;
ll factor[100];
ll tfac[100];
ll s,e;
ll quick_pow(ll x,ll y)
{
    if(y==0) return 1;
    return x*quick_pow(x,--y);
}
void fenjie(ll x)
{
    for(ll i=2;i*i<=x;i++)
    {
        if(x%i==0)
        {
            factor[j++]=i;
            while(x%i==0)
                x=x/i;
        }
    }
    if(x!=1) factor[j++]=x;
}
void dfs(ll x,ll y,ll t)
{
    if(y==t)
    {
        ll p=1;
        for(ll i=0;i<t;i++)
            p*=tfac[i];
        s+=quick_pow(M/p,N);
    }
    else
        for(ll i=x;i<j;i++)
    {
        tfac[y]=factor[i];
        dfs(i+1,y+1,t);
    }
}
int main()
{
    while(scanf("%lld %lld",&N,&M)==2)
    {
        fenjie(M);
        ll e=quick_pow(M,N);
        int flag=-1;
        for(ll i=1;i<=j;i++)
        {
            s=0;
            dfs(0,0,i);
            e+=flag*s;
            flag=-flag;
        }
        cout<<e<<endl;
    }
    return 0;
}
