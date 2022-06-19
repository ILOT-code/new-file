#include<cstdio>
#include<algorithm>
using namespace std;

const int INF = 1 << 30;
const int maxn = 100 + 5;
int m, n, d[maxn][maxn], a[maxn][maxn], Next[maxn][maxn];

int main() {
    while (scanf("%d%d", &m, &n) == 2 && m) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) scanf("%d", &a[i][j]);
        int ans = INF, first = 0;
        for (int j = n - 1; j >= 0; --j)
            for (int i = 0; i < m; ++i) {
                if (j == n - 1) d[i][j] = a[i][j];
                else {
                    int v[3] = {i, i - 1, i + 1};
                    if (i == m - 1) v[2] = 0;
                    if (i == 0) v[1] = m - 1;
                    sort(v, v + 3);
                    d[i][j] = INF;
                    for (int k = 0; k < 3; ++k)
                        if (d[i][j] > d[v[k]][j + 1] + a[i][j]) {
                            d[i][j] = d[v[k]][j + 1] + a[i][j];
                            Next[i][j] = v[k];
                        }
                }
                if (j == 0 && d[i][j] < ans) {
                    ans = d[i][j];
                    first = i;
                }
            }
        printf("%d", first + 1);
        for (int i = Next[first][0], j = 1; j < n; i = Next[i][j], j++) printf(" %d", i + 1);
        printf("\n%d\n", ans);
    }
    return 0;
}