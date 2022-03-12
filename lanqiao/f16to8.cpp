//http://lx.lanqiao.cn/problem.page?gpid=T51
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
char s[100005];
bool d[150000];
char ba[400040];
int main()
{
    scanf("%d",&n);
    d[-1]=d[-2]=d[-3]=0;
    for(int i=1;i<=n;++i){
        scanf("%s",s);
        int ii=0;
        for(;s[ii]!=0;++ii);
        for(int j=0;j<ii;++j){
            if(s[j]>='0'&&s[j]<='9') s[j]=s[j]-'0';
            else                     s[j]=10+s[j]-'A';
            for(int t=3;t>=0;--t)
            {
                d[4*j+t]=s[j]%2;
                s[j]=s[j]/2;
            }
        }
        int T=(4*ii%3==0?4*ii/3:4*ii/3+1);
        for(int jj=1;jj<=T;++jj)
            ba[T-jj]=d[4*ii-jj*3]*4+d[4*ii-jj*3+1]*2+d[4*ii-3*jj+2]+'0';
        printf("%s\n",ba[0]=='0'?ba+1:ba);
    }
    return 0;
}
