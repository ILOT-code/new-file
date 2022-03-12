#include <cstdio>
#include <queue>
using namespace std;
const int M=10000+5;
char s[M];
int len=0;
struct tel
{
    int pos;
    int length;
    bool operator< (tel x) const
    {
        if(length!=x.length) return length<x.length;
        else return pos>x.pos;
    }
};
priority_queue<tel>q;
void find1(int t)
{
    int i=1;
    tel p;
    while(t-i>=0&&t+1+i<len)
    {
        if(s[t-i]==s[t+1+i]) ++i;
        else break;
    };
    p.pos=t-i+1; p.length=2*i;
    q.push(p);
}
void find2(int t)
{
    int i=1;
    tel p;
    while(t-i>=0&&t+2+i<len)
    {
        if(s[t-i]==s[t+2+i]) ++i;
        else break;
    }
    p.pos=t-i+1;p.length=2*i+1;
    q.push(p);
}
int main()
{
    gets(s);
    while(s[len]!=0) len++;
    for(int i=0;i<len;++i)
    {
        if(s[i]==s[i+1]) find1(i);
        if(s[i]==s[i+2]) find2(i);
    }
    if(q.empty()) printf("0");
    else
    {
        tel jie=q.top();
        printf("%d\n",jie.length);
        for(int i=0;i<jie.length;++i)
           printf("%c",s[jie.pos+i]);
    }


    return 0;
}

