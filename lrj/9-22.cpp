//d[i][j]表示i位数，余数为j,需要的最少火柴。
//前导0让我困惑很久。其实为了求解这个数，前导0是必要的。
//比如说数据21，1425，其答案为711075,若不考虑前导0，寻找答案时，075这个数根本不会被找到。
//如果只是要求找到位数，前导0可以不考虑。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
const int maxm = 3000 + 5;
const int INF = 0x3f3f3f3f;
int d[maxn][maxm], vis[maxn][maxm], n, m, remind[10][maxn / 2];
int c[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

void init() {
	int cur = 1, frc = 1;
	for (int i = 0; i <= n / 2; ++i) {
		for (int j = 1; j < 10; ++j) {
			remind[j][i] = cur;
			cur = (cur + frc) % m;
		}
		frc = cur;
	}
}

int main() {
	int kase = 1;
	while (~scanf("%d%d", &n, &m) && n) {
		memset(d, INF, sizeof(d));
		init();
		d[0][0] = 0;
		for (int i = 0; i <= n / 2; ++i)
			for (int j = 0; j < m; ++j)if (d[i][j] < INF)
					for (int k = 0; k <= 9; ++k)if (d[i][j] + c[k] <= n)
							d[i + 1][(10 * j + k) % m] = min(d[i + 1][(10 * j + k) % m], d[i][j] + c[k]);
		int h = n / 2, H, rem = 0, ans[maxn / 2 + 1];
		for (; h; --h) if (d[h][0] < INF) break;
		printf("%d\n", h);
		printf("%d\n", d[4][1075]);
		printf("%d\n", d[3][75]);
		H = h;
		while (h) {
			for (int i = 9; i >= 0; --i) {
				int temp = (m + rem - remind[i][h - 1]) % m;
				if (d[h - 1][temp] + c[i] <= n) {
					ans[h--] = i;
					n -= c[i];
					rem = temp;
					printf("%d %d %d\n", i, rem, n);
					break;
				}
			}
		}
		printf("Case %d: ", kase++);
		if (H == 0) printf("-1");
		else if (ans[H] == 0) printf("0");
		else for (int i = H; i; --i) printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}