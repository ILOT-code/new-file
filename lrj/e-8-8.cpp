//不想写了啊 
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 16384 + 5;
int Rank[maxn], n;

struct Player {
	double a, b, c;
	double totol;
	bool a1, b1, c1;
} players[maxn];


void find1(int i){
	int mins = min(min(players[i+1].a,players[i+1].b),players[i+1].c);
	for(int )




}
int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf%lf", &players[i].a, &players[i].b, &players[i].c);
			players[i].totol = players[i].a + players[i].b + players[i].c;
			players[i].a1 = players[i].b1 = players[i].c1 = 1;
		}
		for (int i = 0; i < n; ++i) scanf("%d", &Rank[i]);

		for (int i = 0; i < n; ++i) {
			if (players[Rank[i]].totol > players[Rank[i + 1]].totol)
				continue;
			if (players[Rank[i]].totol == players[Rank[i + 1]].totol){
				if(Rank[i] < Rank[i+1]) continue;
				if(Rank[i] > Rank[i+1]) find1(i);
			}

		}
	}
	return 0;
}