#include <cstdio>
using namespace std;
int const M=10+5,N=10+5;
int main()
{
    int a[M][N],m,n;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&a[i][j]);
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
            printf("%d ",a[1+m-j][i]);
        printf("\n");
    }
    return 0;
}

