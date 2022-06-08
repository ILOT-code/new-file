//http://poj.org/problem?id=1184
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define INF 10000003
using namespace std;
struct  Node
{
    int num[6],pos,zt,step;
}save[720*6*10];
bool pd[47000][10+2][6+1]; //6^6=46656;实际上只有6！种，但是在找到的一个可以给各种排列编号的函数计算量大。
char s1[10],s2[10];
int ct=0;
int six_N(int num[])       //每种排列都看成一个六进制的数，将其转化为十进制。
{
    int ret=0;
    for(int i=0;i<6;++i){
        ret*=6;ret+=num[i];
    }return ret;
}
void change(Node &in,int ii) //定义各种操作
{
    if(ii==0)
    {
        if(in.pos) in.pos--;
    }
    else if(ii==1)
    {
        if(in.pos<5) in.pos++;
        if(in.pos==5) in.zt=9;
        else
        {
            if(in.zt<=4&&in.pos>in.zt)   in.zt++;
            if(in.zt>=5&&in.pos>in.zt-5) in.zt++;
        }
    }
    else if(ii==2)
    {
        int t=in.num[in.pos];in.num[in.pos]=in.num[0];in.num[0]=t;
    }
    else if(ii==3)
    {
        int t=in.num[in.pos];in.num[in.pos]=in.num[5];in.num[5]=t;
        if(in.zt<5) in.zt+=5;
    }
    in.step++;
}
void bfs()
{
    queue<Node>Q;
    memset(pd,0,sizeof(pd));
    Node now, next;
    for(int i=0;i<6;i++) now.num[i]=i;
    now.zt=0;  now.pos=0; now.step=0;
    pd[six_N(now.num)][now.zt][now.pos]=1;
    Q.push(now);
    while(!Q.empty())
    {
        now=Q.front(); Q.pop();
        save[ct++]=now;
        for(int i=0;i<4;i++)
        {
            next=now;
            change(next,i);
            int tem=six_N(next.num);
            if(pd[tem][next.zt][next.pos]) continue;
            pd[tem][next.zt][next.pos]=1;
            Q.push(next);
        }
    }
}
void sol()
{
    int ret=INF;
    for(int i=0;i<ct;++i)
    {
        int flag=1,sum=0;
        int tt=save[i].zt;
        if(tt>4) tt-=5;
        for(int j=0;j<6;j++)
        {
            int dd=0;
            if(j<=4&&j<=tt)  dd=1;
            else if(j==5&&save[i].zt>=5) dd=1;
            int pre=save[i].num[j];
            if(dd==1)  sum+=abs(s1[pre]-s2[j]) ;
            else if(dd==0&&s1[pre]!=s2[j])
            {
                flag =0; break;
            }
        }
        if(flag) ret = min(ret,save[i].step+sum);
    }
    printf("%d\n", ret);
}
int main()
{
    bfs();
    scanf("%s%s", s1, s2);
    for(int i = 0; i < 6; i++) s1[i] -= '0', s2[i] -= '0';
    sol();
    return 0;
}
