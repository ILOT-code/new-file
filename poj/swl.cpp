//http://poj.org/problem?id=1182
#include<cstdio>
#include<iostream>
#define N 50005
#define K 100005
using namespace std;
int n,k;
struct node
{
    int pre;
    int rel;
}p[N];
int find(int x)
{
    if(p[x].pre==x)
        return x;
    int temp=p[x].pre;
    p[x].pre=find(temp);
    p[x].rel=(p[temp].rel+p[x].rel)%3;
    return p[x].pre;
}
int main()
{
    scanf("%d %d",&n,&k);
        for(int i=1;i<=n;i++)
        {
            p[i].pre=i;
            p[i].rel=0;
        }
        int sum=0,ope,x,y;
        for(int i=1;i<=k;i++)
        {
            scanf("%d %d %d",&ope,&x,&y);
            if(x>n||y>n||(ope==2&&x==y))
                continue;
            int rootx,rooty;
            rootx=find(x);
            rooty=find(y);
            if(rootx!=rooty)
            {
                p[rooty].pre=rootx;
                p[rooty].rel=(ope-1+p[x].rel-p[y].rel+3)%3;
                sum++;
            }
            else
                sum+=!((p[y].rel-p[x].rel+3)%3-(ope-1));
        }
        printf("%d\n",k-sum);
    return 0;
}
