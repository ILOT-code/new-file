#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
//flag = 1, 1，后手，电脑作决策,+.
const int INF = 0x3f3f3f3f;
const int maxn = 362880 + 10;
int cnt, x, y;
vector<PII> bestsons;
struct State {
	int a[3][3], score, free;
	bool flag;
	State(bool f = 0) {
		memset(a, 0, sizeof(a));
		score = 0; free = 9;
		flag = f;
	}
} states[maxn];

int h(State& now) {
	bool isend = 0;
	for (int i = 0; i < 3; ++i)
		if ((now.a[i][0] != 0 && now.a[i][0] == now.a[i][1] && now.a[i][0] == now.a[i][2])
		        || (now.a[0][i] != 0 && now.a[0][i] == now.a[1][i] && now.a[0][i] == now.a[2][i])) {isend = 1; break;}
	if (now.a[1][1] != 0 && ((now.a[0][0] == now.a[1][1] && now.a[0][0] == now.a[2][2])
	                         || (now.a[0][2] == now.a[1][1] && now.a[0][2] == now.a[2][0]))) isend = 1;
	if (isend == 0) return now.score = 0;
	else return now.score = now.flag == 1 ? -1 : 1;
}
char trans(int color) {
	if (color == 1) return '+';
	if (color == -1) return '-';
	else return ' ';
}
void draw(State& now) {
	for (int i = 0; i < 3; ++i) {
		printf("%c|%c|%c\n", trans(now.a[i][0]), trans(now.a[i][1]), trans(now.a[i][2]));
	}
}
State luozi(State& now) {
	State next;
	next = now;
	while (x < 0 || x > 2 || y < 0 || y > 2 || now.a[x][y] != 0) {
		printf("落子不被接受，请重新选择！\n");
		scanf("%d%d", &x, &y);
	}
	next.a[x][y] = next.flag == 1 ? 1 : -1;
	next.free -= 1;
	next.flag ^= 1;
	next.score = h(next);
	return next;
}

int alpha_beta(int u, int alph, int beta, bool is_max) {
	if (states[u].free == 0) return states[u].score;
	if (states[u].score != 0) return states[u].score;
	if (is_max) {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j) if (states[u].a[i][j] == 0) {
					int d = ++cnt;
					states[d] = states[u];
					states[d].a[i][j] = states[d].flag == 1 ? 1 : -1;
					states[d].free -= 1;
					states[d].flag ^= 1;
					states[d].score = h(states[d]);
					int tmp = alpha_beta(d, alph, beta, is_max ^ 1);
					alph = max(alph, tmp);
					if (u == 0 && tmp == alph) bestsons.push_back(PII(i, j));
					if (alph >= beta) break;
				}
		return alph;
	} else {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j) if (states[u].a[i][j] == 0) {
					int d = ++cnt;
					states[d] = states[u];
					states[d].a[i][j] = states[d].flag == 1 ? 1 : -1;
					states[d].free -= 1;
					states[d].flag ^= 1;
					states[d].score = h(states[d]);
					beta = min(beta, alpha_beta(d, alph, beta, is_max ^ 1));
					if (alph >= beta) break;
				}
		return beta;
	}
}
void AI(State now) {
	bestsons.clear();
	states[0] = now;
	cnt = 0;
	alpha_beta(0, -INF, INF, 1);
	srand((int)time(NULL));
	int t = rand() % bestsons.size();
	x = bestsons[t].first, y = bestsons[t].second;
}
int main() {
	State game;
	draw(game);
	while (game.free > 0) {
		if (game.flag == 0) {printf("请您下子：\n"), scanf("%d%d", &x, &y);}
		else {printf("AI落子为:\n"), AI(game);}
		game = luozi(game);
		draw(game);
		if (game.score == 1) {printf("+胜利\n"); break;}
		if (game.score == -1) {printf("-胜利\n"); break;}
	}
	if (game.score == 0) printf("平局\n");
	return 0;
}
