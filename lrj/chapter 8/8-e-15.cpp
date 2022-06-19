#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;

struct Node{
	int l, r;
	bool operator<(const Node &rhs) const{
		return r < rhs.r || (r == rhs.r && l < rhs.l);
	}
} p[maxn];

int main(){
	int T, n;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].l, &p[i].r);
		sort(p, p + n);
		int ans = 0, pos = p[0].r;
		for(int i = 1; i < n; ++i){
			if(p[i].l > pos){
				ans++;
				pos = p[i].r;
				continue;
			}
			if(p[i].r == pos) continue;
			else pos++;
		}
		printf("%d\n",ans);
	}
	return 0;
}