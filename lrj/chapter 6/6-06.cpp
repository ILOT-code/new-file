//简单思路 运算量过大
/*
#include <cstdio>
#include <cstring>
const int maxd=20;
int s[(1<<maxd)+5];
int main(){
    int D,I,t;
    scanf("%d%d",&D,&I);
    for(int i=1;i<=I;++i){
        t=1;
        for(int j=1;j<D;++j){
            if(s[t])  { s[t]=0;t=2*t+1; continue;}
            s[t]=1;t=2*t;
        }
    }
    printf("%d",t);
}
*/
#include <cstdio>
using namespace std;
int main() {
    int D, I;
    while (scanf("%d%d", &D, &I)) {
        int k = 1;
        for (int i = 1; i < D; ++i) {
            if (I % 2) {k *= 2; I = I / 2 + 1;}
            else {k = 2 * k + 1; I = I / 2;}
        }
        printf("%d\n", k);
    }
    return 0;
}