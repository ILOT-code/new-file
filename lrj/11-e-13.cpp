#include<cstdio>
#include<map>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define PII pair<int,int>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 50 + 5;
const int maxw = 300 + 5;
const int d1[4][2] = {{0, 1}, {1, 0}, {0, -1}, { -1, 0}};
const int d2[4][2] = {{1, 1}, {1, -1}, { -1, -1}, { -1, 1}};

int maps[maxw][maxw], X_cnt, Y_cnt;
map<int, int> RX, RY;
void unique() {
	X_cnt = Y_cnt = 0;
	for (auto& x : RX) x.se = ++X_cnt;
	for (auto& y : RY) y.se = ++Y_cnt;
}

void fillmap(int lx, int ly, int rx, int ry) {
	int x1, x2, y1, y2;
	int a = 3 * RX[lx] + 1, b = 3 * RX[rx] - 1;
	int c = 3 * RY[ly] + 1, d = 3 * RY[ry] - 1;
	for (int i = a; i <= b; ++i) {
		for (int j = c; j <= d; ++j) {
			maps[i][j] = 1;
			if (i != a && i != b && i != c && i != d) continue;
			for (int k = 0; k < 4; ++k) {
				x1 = i + 2 * d1[k][0], y1 = j + 2 * d1[k][1];
				x2 = i + d1[k][0],   y2 = j + d1[k][1];
				if (maps[x1][y1]) maps[x2][y2] = 1;
				x1 = i + 2 * d2[k][0], y1 = j + 2 * d2[k][1];
				x2 = i + d2[k][0],   y2 = j + d2[k][1];
				if (maps[x1][y1]) maps[x2][y2] = 1;
			}
		}
	}
}

struct Node {
	int x, y, d, D;
	Node(int x = 0, int y = 0, int d = -1, int D = 0): x(x), y(y), d(d) , D(D) {}
	bool operator<(const Node& rhs) const { return D > rhs.D;};
};
int dis[maxw][maxw][4];
void dijkstra(int sx, int sy, int ex, int ey) {
	PII st, ed;
	st = PII(3 * RX[sx], 3 * RY[sy]);
	ed = PII(3 * RX[ex], 3 * RY[ey]);
	priority_queue<Node> Q;
	memset(dis, INF, sizeof(dis));
	for (int i = 0; i < 4; ++i) {
		Q.push(Node(st.fi, st.se, i, 0));
		dis[st.fi][st.se][i] = 0;
	}
	int ans = INF;
	while (!Q.empty()) {
		Node P = Q.top(); Q.pop();
		int x = P.x, y = P.y, d = P.d;
		if (P.D != dis[x][y][d]) continue;
		if (x == ed.fi && y == ed.se) { ans = P.D; break; }
		for (int i = 0; i < 4; ++i) {
			int turn = (d != i);
			int tx = x + d1[i][0], ty = y + d1[i][1];
			if (maps[tx][ty] || tx <= 0 || tx > 3 * X_cnt || ty <= 0 || ty > 3 * Y_cnt) continue;
			if (dis[tx][ty][i] > dis[x][y][d] + turn) {
				dis[tx][ty][i] = dis[x][y][d] + turn;
				Q.push(Node(tx, ty, i, dis[tx][ty][i]));
			}
		}
	}
	printf("%d\n", ans == INF ? -1 : ans);
}

int main() {
	int n, sx, sy, ex, ey;
	int lx[maxn], ly[maxn], rx[maxn], ry[maxn];
	while (~scanf("%d %d %d %d", &sx, &sy, &ex, &ey)) {
		if (sx == 0 && sy == 0 && ex == 0 && ey == 0) break;
		scanf("%d", &n);
		RX.clear(); RY.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &lx[i], &ly[i], &rx[i], &ry[i]);
			if (lx[i] > rx[i]) swap(lx[i], rx[i]);
			if (ly[i] > ry[i]) swap(ly[i], ry[i]);
			RX[lx[i]] = RX[rx[i]] = 1; RY[ly[i]] = RY[ry[i]] = 1;
		}
		RX[sx] = RX[ex] = 1; RY[sy] = RY[ey] = 1;

		unique();
		memset(maps, 0, sizeof(maps));
		for (int i = 0; i < n; ++i) fillmap(lx[i], ly[i], rx[i], ry[i]);
		dijkstra(sx, sy, ex, ey);
	}
	return 0;
}