#include <cstdio>
using namespace std;
const int maxn=100005;
int n,m,ope,pos1,pos2,right[maxn],left[maxn];
int main(){
    while(scanf("%d%d",&n,&m)){
        int flag=1,sum=0,summ=0,cont=1;
        for(int i=0;i<=n;++i){
            right[i]=i+1;
            left[i]=i-1;
            sum+=i;
        }
        for(int i=1;i<=m;++i){
            scanf("%d%d%d",&ope,&pos1,&pos2);
            if(ope==1){
                if(right[pos1]==pos2) continue;
                right[left[pos1]]=right[pos1];
                left[right[pos1]]=left[pos1];
                right[pos1]=pos2;
                left[pos1]=left[pos2];
                right[left[pos2]]=pos1;
                left[pos2]=pos1;
            }
            if(ope==2){
                if(left[pos1]==pos2) continue;
                left[right[pos1]]=left[pos1];
                right[left[pos1]]=right[pos1];
                left[pos1]=pos2;
                right[pos1]=right[pos2];
                left[right[pos2]]=pos1;
                right[pos2]=pos1;
            }
            if(ope==3){
                if(right[pos1]==pos2){
                    right[pos1]=right[pos2]; left[right[pos2]]=pos1;
                    right[left[pos1]]=pos2;  left[pos2]=left[pos1];
                    right[pos2]=pos1;        left[pos1]=pos2;
                }
                else if(left[pos1]==pos2){
                    left[pos1]==left[pos2];  right[left[pos2]]=pos1;
                    left[right[pos1]]=pos2;  right[pos2]=right[pos1];
                    left[pos2]=pos1;         right[pos1]=pos2;
                }
                else{
                    int pos2_left=left[pos2],pos2_right=right[pos2];
                    left[pos2]=left[pos1]; right[pos2]=right[pos1];
                    right[left[pos1]]=pos2;left[right[pos1]]=pos2;
                    left[pos1]=pos2_left;  right[pos1]=pos2_right;
                    right[pos2_left]=pos1; left[pos2_right]=pos1;
                }
            }
            if(ope==4){
                flag++;
            }
        }
        for(int i=right[0];i!=n+1;i=right[i])
        if(cont++%2) summ+=i;
        printf("%d\n",(flag%2==0&&n%2==0)? sum-summ:summ);
    }
    return 0;
}