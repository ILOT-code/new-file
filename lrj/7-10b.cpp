#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 9;
int n, a[maxn];

// the number of integers with incorrect successor
int h() {
  int cnt = 0;
  for (int i = 0; i < n - 1; i++)
    if (a[i] + 1 != a[i + 1]) cnt++;
  if (a[n - 1] != n) cnt++;
  return cnt;
}

bool dfs(int d, int maxd) {
  if (d * 3 + h() > maxd * 3) return false;
  if (h() == 0) return true;
  int b[maxn], olda[maxn];
  memcpy(olda, a, sizeof(a));
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++) {
      int cnt = 0;
      for (int k = 0; k < n; k++)
        if (k < i || k > j) b[cnt++] = a[k];
      for (int k = 0; k <= cnt; k++) {
        int cnt2 = 0;
        for (int p = 0; p < k; p++) a[cnt2++] = b[p];
        for (int p = i; p <= j; p++) a[cnt2++] = olda[p];
        for (int p = k; p < cnt; p++) a[cnt2++] = b[p];
        if (dfs(d + 1, maxd)) return true;
        memcpy(a, olda, sizeof(a));
      }
    }
  return false;
}
int solve() {
  if (h() == 0) return 0;
  for (int maxd = 1; maxd < 9; maxd++)
    if (dfs(0, maxd)) return maxd;
}
int main() {
  int kase = 0;
  while (scanf("%d", &n) == 1 && n) {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Case %d: %d\n", ++kase, solve());
  }
  return 0;
}