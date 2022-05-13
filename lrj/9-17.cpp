//逆推，采用填表法,速度不知道为什么比顺推的刷表法满了无数倍。
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
using namespace std;

const double INF = 1e30;
const int maxn = 8;
const int maxm = 100 + 5;
const int maxstate = 15000;
int m, n, s[maxn], k[maxn], kk;
double c, price[maxn][maxm];
char name[maxn][10];
double d[maxm][maxstate];
int opt[maxm][maxstate], Prev[maxm][maxstate];
int buy_next[maxstate][maxn], sell_next[maxstate][maxn];
vector<vector<int> > states;
map<vector<int>, int> ID;

void dfs(int state, vector<int> &lots, int totlot) {
	if (state == n) {
		ID[lots] = states.size();
		states.push_back(lots);
		return;
	}
	for (int i = 0; i <= k[state] && i + totlot <= kk; ++i) {
		lots[state] = i;
		dfs(state + 1, lots, totlot + i);
	}
}

void init() {
	states.clear();
	ID.clear();
	vector<int> lots(n);
	dfs(0, lots, 0);

	for (int s = 0; s < states.size(); ++s) {
		int totlot = 0;
		for (int i = 0; i < n; ++i) totlot += states[s][i];
		for (int i = 0; i < n; ++i) {
			buy_next[s][i] = sell_next[s][i] = -1;
			if (states[s][i] < k[i] && totlot < kk) {
				vector<int> newstate = states[s];
				newstate[i]++;
				buy_next[s][i] = ID[newstate];
			}
			if (states[s][i] > 0) {
				vector<int> newstate = states[s];
				newstate[i]--;
				sell_next[s][i] = ID[newstate];
			}
		}
	}
	for (int day = 0; day < m; ++day)
		for (int s = 0; s < states.size(); ++s) d[day][s] = -INF;
	d[0][0] = c; d[m][0] = -INF;
}

void update(int day, int s, int s2, double v, int o) {
	if (v > d[day][s]) {
		d[day][s] = v;
		Prev[day][s] = s2;
		opt[day][s] = o;
	}
}
double dp(int day, int state) {
	if(day == 0 && state == 0) return c;
	if(day == 0) return -INF;
	if (d[day][state] >= 0) return d[day][state];
	double temp1 = dp(day - 1, state); update(day, state, state, temp1, 0);
	for (int i = 0; i < n; ++i) {
		if (sell_next[state][i] >= 0) {
			double temp2 = dp(day - 1, sell_next[state][i]);
			if (temp2 >= price[i][day - 1] - 1e-3) update(day, state, sell_next[state][i], temp2 - price[i][day - 1], i + 1);
		}
		if (buy_next[state][i] >= 0) {
			double temp3 = dp(day - 1, buy_next[state][i]);
			update(day, state, buy_next[state][i], temp3 + price[i][day - 1], -i - 1);
		}
	}
	return d[day][state];
}

void print_ans(int day, int s) {
	if (day == 0) return;
	print_ans(day - 1, Prev[day][s]);
	if (opt[day][s] == 0) printf("HOLD\n");
	else if (opt[day][s] > 0) printf("BUY %s\n", name[opt[day][s] - 1]);
	else printf("SELL %s\n", name[-opt[day][s] - 1]);
}

int main() {
	int kase = 0;
	while (scanf("%lf%d%d%d", &c, &m, &n, &kk) == 4) {
		if (kase++ > 0) printf("\n");
		for (int i = 0; i < n; i++) {
			scanf("%s%d%d", name[i], &s[i], &k[i]);
			for (int j = 0; j < m; j++) { scanf("%lf", &price[i][j]); price[i][j] *= s[i]; }
		}
		init();
		printf("%.2lf\n", dp(m,0));
		print_ans(m, 0);
	}
	return 0;
}