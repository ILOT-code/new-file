// 很离谱
#include <cstring>
#include <cstdio>
#include <queue>
#include <malloc.h>
using namespace std;
int fact[9];
int main(){
    int t=0;
    while(t<3){
        for(int i=0;i<2;++i){
            int *x;
            (*x)++;
            printf("%d",*x);
            printf(" ");
            printf("%d",&x);
            printf("   ");
        }
        printf("\n");
        ++t;
    }
}
//结果
//12325970 6815248   12325971 6815248   
//12325972 6815248   12325973 6815248
//12325974 6815248   12325975 6815248