#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<utility>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
#define EPS 1e-9
#define PI acos(-1.0)
#define INF 0x3f3f3f3f
#define LL long long
const int MOD = 1E9+7;
const int N = 2000+5;
const int dx[] = {0,0,-1,1,-1,-1,1,1};
const int dy[] = {-1,1,0,0,-1,1,-1,1};
using namespace std;

LL n,m;
LL factor[N];
LL sum[N];
LL num,cnt;
void Get_Factor() { //�ֽ�������
    num=0;
    LL temp=m;
    for(LL i=2; i*i<=temp; i++) {
        if(temp%i==0) {
            factor[num++]=i;
            while(temp%i==0)
                temp=temp/i;
        }
    }
    if(temp!=1)
        factor[num++]=temp;
}

LL quick_pow(LL a,LL b) {
    LL r=1,base=a;
    while(b) {
        if(b&1)
            r*=base;
        base*=base;
        b>>=1;
    }
    return r;
}

LL dfs(LL a,LL b,LL c) {//dfs�õ���Ƭ��n+1������c�Ĺ�����ʱ�ķ�����
    if(b==c) {
        LL temp=m;
        for(LL i=0; i<c; i++)
            temp/=sum[i];//��ʾ[1,x]���ж��ٸ����Ǳ���
        cnt+=quick_pow(temp,n);//ѡn������ÿ����x��ѡ��
    } else {
        for(LL i=a; i<num; i++) {
            sum[b]=factor[i];
            dfs(i+1,b+1,c);
        }
    }
}

int main() {
    while(scanf("%lld%lld",&n,&m)!=EOF&&(n+m)) {
        Get_Factor();
        LL res=quick_pow(m,n);//m^n

        for(LL i=1; i<=num; i++) {
            cnt=0;
            dfs(0,0,i);

            if(i%2)//���ż��
                res-=cnt;
            else
                res+=cnt;
            cout<<res<<endl;
        }
        printf("%lld\n",res);
    }
    return 0;
}
