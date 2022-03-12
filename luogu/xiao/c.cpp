#include<cstring>
#include<cstdio>
using namespace std;
int T,L,R;
bool isComp[10000005];
void fint(int n)
{
	isComp[1]=0;
	for(int i=2;i*i<=n;i++)
	{
	    if(isComp[i]==1)
	        for(int j=i*i;j<=n;j+=i)
	        	isComp[j]=0;
	}
}
int main()
{
    scanf("%d",&T);
    memset(isComp,1,sizeof(isComp));
    for(int i=1;i<=T;++i)
    {
        int c=0;
        scanf("%d %d",&L,&R);
        fint(R);
        for(int i=L;i+2<=R;i++)
            if(isComp[i]&&isComp[i+2]) c++;
        printf("%d\n",c);
    }
    return 0;
}
