//考虑一个状态A，设它到达终点的期望步数为ans;
//下一条边总共有N=n*(n-1)条选择，其中sum种是有效的，其它的选择都是在一个连通集里面重复选。
//则ans=(N-sum)/N*(ans+1)+求和：xi/N*(dp[S']+1);
//变换得到sum/N*ans=(N-sum)/N+求和：xi/N*(dp[S']+1);
//其中N-sum是没用的种数，求和：xi是有用的种数，则它们相加=N。
//则ans=N/sum + 求和xi/sum*dp[S'].
//这就是下面的状态转移函数。
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 32;
struct node {
	int a[maxn];
	double res;
	bool operator==(const node& rhs) {
		for (int i = 1; i <= 30; ++i)
			if (a[i] != rhs.a[i]) return 0;
		return 1;
	}
};
vector<int>G[maxn];
int n, m, vis[maxn];
node start;

bool read_list() {
	if (scanf("%d%d", &n, &m) != 2) return false;;
	for (int i = 1; i <= n; ++i) G[i].clear();
	memset(vis, 0, sizeof(vis));
	for (int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	return true;
}

int dfs(int u) {
	vis[u] = 1;
	int res = 1;
	for (int i = 0; i < G[u].size(); ++i)
		if (!vis[G[u][i]]) res += dfs(G[u][i]);
	return res;
}
vector<node> st;
const int maxhash = 1000007;
int head[maxhash], Next[maxhash * 3];//理论上是2^30,但maxhash*3也够了。

int Hash(const node& A) {
	int res = 0;
	for (int i = 1; i <= n; ++i)
		res = (res * 10 + A.a[i]) % maxhash;
	return res;
}

int Vis(node& A, int& ok) {
	int id = Hash(A);
	for (int p = head[id]; p != -1; p = Next[p])
		if (st[p] == A) {
			ok = 1;  return p;
		}
	st.push_back(A);
	int u = st.size() - 1;
	Next[u] = head[id];
	head[id] = u;
	return u;
}

double dp(node& A) {
	int ok = 0, id = Vis(A, ok);
	if (ok) return st[id].res;
	if (A.a[n] == 1) return st[id].res = 0;
	int sum = n * (n - 1);
	double ans = 0;
	for (int i = 1; i <= n; ++i)
		if (A.a[i]) sum -= A.a[i] * i * (i - 1);
	ans = (n * (n - 1) * 1.0) / (sum);
	for (int i = 1; i <= n; ++i)if (A.a[i]) {
			for (int j = i; j <= n; ++j) if (A.a[j]) {
					if (i == j && A.a[j] == 1) continue;
					int ij = A.a[i] * A.a[j] * 2;
					if (i == j) ij = A.a[i] * (A.a[j] - 1);
					A.a[i]--; A.a[j]--; A.a[i + j]++;
					ans += dp(A) * (i * j * ij) / sum;
					A.a[i]++; A.a[j]++; A.a[i + j]--;
				}
		}
	return st[id].res = ans;
}

int main() {
	while (read_list()) {
		for (int i = 1; i < maxn; ++i) start.a[i] = 0;
		for (int i = 1; i <= n; ++i)
			if (!vis[i]) start.a[dfs(i)]++;
		st.clear();
		memset(head, -1, sizeof(head));
		printf("%.6lf\n", dp(start));
	}
}
