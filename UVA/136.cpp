// from UVA 136
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;
typedef long long LL;
int list[3]={2,3,5};
int main(){
  priority_queue< LL ,vector<LL>, greater<LL> >pq;
  set<LL>s;
  int count=0;
  LL x,y;
  pq.push(1);
  for(int i=1;i<=1500;++i){
    x=pq.top(); pq.pop();
    for(int j=0;j<3;++j){
      y=x*list[j];
      if(s.count(y)) continue;
      pq.push(y);
      s.insert(y);
    }
  }
  cout<<x;
  return 0;
}
