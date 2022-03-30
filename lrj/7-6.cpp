//枚举排序
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=10;
int id[256],letter[maxn];
int main(){
    char input[1000];
    while(scanf("%s,input")==1&&input[0]!='#'){
        int n=0;
        for(char ch='A';ch<='Z';++ch){
            if(strchr(input,ch)!=NULL){
                id[ch]=n++;
                letter[n]=ch;
            }
        }
        int len=strlen(input),p=0,q=0;
        vector<int> u,v;
        for(;;){
            while(p<len&&input[p]!=':') p++;
            if(p==len) break;
            while(q<len &&input[q]!= ';') q++;
            for(int i=p+1;i<q;i++) {
            u.push_back(id[input[p-1]]);
            v.push_back(id[input[i]]);
            }
        p++; q++;
        }
        int P[maxn],bestP[maxn],pos[maxn],ans=n;
        for(int i=0;i<n;i++) P[i]=i;
        do {
            for(int i=0;i<n;i++) pos[P[i]]=i; 
            int bandwidth=0;
            for(int i=0;i<u.size();i++)
                bandwidth=max(bandwidth,abs(pos[u[i]]-pos[v[i]]));
            if(bandwidth<ans){
            ans=bandwidth;
            memcpy(bestP,P,sizeof(P));
            }
        }while(next_permutation(P,P+n));
        for(int i=0;i<n;i++) printf("%c ",letter[bestP[i]]);
        printf("-> %d\n", ans);
    }
    return 0;

}