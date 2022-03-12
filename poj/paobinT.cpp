#include <cstdio>
#include <cstring>
using namespace std;
#define max(a,b) (a) > (b) ? (a) : (b)

int N,M;
char map[110][20],num[110],top;
int stk[70],cur[110];
int dp[110][70][70];

inline bool ok(int x){  //�жϸ�״̬�Ƿ�Ϸ��������������ڵ�1֮��ľ���С��3��
   if(x&(x<<1)) return 0;
   if(x&(x<<2)) return 0;
   return 1;
}
//�ҵ����п��ܵĺϷ�״̬�����60��
inline void jinit()
{
   top=0;
   int i,total=1<<N;
   for(i=0;i<total;i++) if(ok(i)) stk[++top]=i;
}
//�ж�״̬x�Ƿ����k��ƥ��
inline bool fit(int x,int k)
{
   if(cur[k]&x) return 0;
   return 1;
}
//��һ��������x�Ķ�������1�ĸ���(���ڳ�ʼ��)
inline int jcount(int x)
{
   int cnt=0;
   while(x)
   {
       cnt++;
       x&=(x-1);
   }
   return cnt;
}

int main(){
   while(scanf("%d%d",&M,&N) != EOF){
       if(N == 0 && M == 0)break;
       jinit();
       for(int i = 1; i <= M; ++i)scanf("%s",map[i]+1);
       for(int i = 1; i <= M; ++i)
       for(int j = 1; j <= N; ++j){
           cur[i]=0;
           for(j=1;j<=N;j++){
                if(map[i][j]=='H')cur[i]+=(1<<(j-1));
           }
       }
       memset(dp,-1,sizeof(dp));

       //��ʼ����һ��״̬
       for(int i = 1;i <= top;i++){
           num[i]=jcount(stk[i]);
           if(fit(stk[i],1))
                dp[1][1][i]=num[i];
       }
       int i,t,j,k;
       for(i = 2;i <= M;i++){
           for(t = 1;t <= top;t++){
                if(!fit(stk[t],i)) continue;
                for(j = 1;j <= top;j++)
                {
                    if(stk[t]&stk[j])continue;
                    for(k = 1;k <= top;k++)
                    {
                        if(stk[t]&stk[k])continue;
                        if(dp[i-1][j][k]==-1)continue;
                        dp[i][k][t] =max(dp[i][k][t],dp[i-1][j][k]+num[t]);
                    }
                }
           }
       }
       int ans = 0;
       for(i = 1; i <= M; ++i)
       for(j = 1; j <= top; ++j)
       for(k = 1; k <= top; ++k)
       ans = max(ans,dp[i][j][k]);
       printf("%d\n",ans);
   }
   return 0;
}
