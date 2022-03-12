//https://www.luogu.com.cn/problem/P1379
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;
const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
char c;
int x0,y0;
struct matrix
{
    int a[5][5];
    bool operator< (matrix x) const{
        for(int i=1;i<=3;++i)
            for(int j=1;j<=3;++j)
            if(a[i][j]!=x.a[i][j]) return (a[i][j]>x.a[i][j]);
        return false;
    }
}st,f;
int h(matrix x){
    int ret=0;
    for(int i=1;i<=3;++i)
        for(int j=1;j<=3;++j)
        if(st.a[i][j]!=0&&x.a[i][j]!=st.a[i][j]) ret++;
    return ret;
}
struct node{
    matrix a;
    int t;
};
bool operator<(const node x,const node y) { return x.t+h(x.a)>y.t+h(y.a);}

priority_queue<node,vector<node>>q;
set<matrix>s;
int main()
{
  st.a[1][1]=1; st.a[1][2]=2; st.a[1][3]=3;
  st.a[2][1]=8; st.a[2][2]=0; st.a[2][3]=4;
  st.a[3][1]=7; st.a[3][2]=6; st.a[3][3]=5;
  for(int i=1;i<=3;++i)
    for(int j=1;j<=3;++j){
      scanf("%c",&c);
      f.a[i][j]=c-'0';
  }
  q.push({f,0});
  s.insert(f);
  while(!q.empty())
{
      node now,next;
      now=q.top();
      q.pop();
      if(!h(now.a)) {
        printf("%d\n",now.t);
        return 0;
      }
      for(int i=0;i<9;++i)
        if(!now.a.a[1+i/3][i-(i/3)*3+1]){
          x0=1+i/3;y0=i+1-(i/3)*3;
          break;
      }
      for(int i=0;i<4;++i)
      {
          int xx=x0+dx[i],yy=y0+dy[i];
          if(1<=xx&&3>=xx&&1<=yy&3>=yy)
          {
              next=now;
              swap(next.a.a[xx][yy],next.a.a[x0][y0]);
              if(!s.count(next.a))
              {
                  s.insert(next.a);
                  q.push({next.a,next.t+1});
              }
          }
      }
  }
  return 0;
}
