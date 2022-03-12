//http://poj.org/problem?id=1061
#include <iostream>
using namespace std;
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    long long r=exgcd(b,a%b,y,x);
        y=y-a/b*x;
    return r;
}
int main()
{
    long long x,y,m,n,L;
    while(scanf("%lld %lld %lld %lld %lld",&x,&y,&m,&n,&L)==5)
       {
           long long a=n-m,b=L,c=x-y,s,k,r;
           r=exgcd(a,b,s,k);
           if(c%r) {cout<<"Impossible"<<endl; continue;}
           else {
                s*=c/r;
                s%=(b/r);
                while(s<0) s=s+(b/r);
                cout<<s<<endl;
           }}
           return 0;
}

