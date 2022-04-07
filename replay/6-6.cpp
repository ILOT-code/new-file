#include <cstdio>
using namespace std;
int main(){
    int D,I;
    while(scanf("%d%d",&D,&I)){
        int k=1;
        for(int d=1;d<D;++d){
            if(I%2==0){
                k=2*k+1;
                I=I/2;
            }
            else{
                k=2*k;
                I=I/2+1;
            }
        }
        printf("%d\n",k);
    }
    return 0;
}