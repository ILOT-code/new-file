#include <cstdio>
#include <algorithm>
using namespace std;
bool cmp(char a,char b)
{return a>b;}
int const M=80+10;
int main()
{
    int n,i=0;
    char s[M];
    scanf("%d",&n);
    getchar();
    gets(s);
    while(s[i]!=0)
    {
        if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')))
        {
            int t=i;
            while(s[t]!=0)
                {
                    s[t]=s[t+1];
                    ++t;

                };
        }
        else i++;
    };
    i=0;
    while(s[i]!=0)
    {
        if(s[i]>='A'&&s[i]<='Z') s[i]+=32;
        else if(s[i]>='a'&&s[i]<='z') s[i]-=32;
        ++i;
    };
    i=0;
    while(s[i]!=0)
    {
        int t=i+1;
        while(s[t]!=0)
        {
            if(s[t]==s[i])
            {
                 int j=t;
                  while(s[j]!=0)
                {
                    s[j]=s[j+1];
                    ++j;

                };
            }
            ++t;
        };
        ++i;
    };
    sort(s,s+i,cmp);
    for(;n>0;--n)
   {
       for(int j=0;j<i;++j)
        printf("%c",s[j]);
   }
   return 0;
}


