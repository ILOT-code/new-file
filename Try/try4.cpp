#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 10000000;
const int maxn = 100 + 5;
int m, n, d[maxn][maxn], a[maxn][maxn], Next[maxn][maxn];
int main() {
    while (~scanf("%d%d", &m, &n) == 2 && m) {

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);

        /*  int ans = INF, first = 0;
            for (int j = n - 1; j >= 0; --j)
                for (int i = 0; i < m; ++i) {
                    if (j == n - 1) {d[i][j] = a[i][j]; continue;}
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
                    if (j == 0 && d[i][j] < ans) {
                        ans = d[i][j];
                        first = i;
                    }
                }*/
        int ans = INF, first = 0;
        for (int j = n - 1; j >= 0; j--)
            for (int i = 0; i < m; i++) {
                if (j == n - 1) d[i][j] = a[i][j];
                else {
                    int rows[3] = {i, i - 1, i + 1};
                    if (i == 0) rows[1] = m - 1;
                    if (i == m - 1) rows[2] = 0;
                    sort(rows, rows + 3);
                    d[i][j] = INF;
                    for (int k = 0; k < 3; k++) {
                        int v = d[rows[k]][j + 1] + a[i][j];
                        if (v < d[i][j]) { d[i][j] = v; Next[i][j] = rows[k]; }
                    }
                }
                if (j == 0 && d[i][j] < ans) { ans = d[i][j]; first = i; }
            }

        //  for (int i = first, j = 0; j < n; i = Next[i][j], j++) printf("%d ", i + 1);
        //  printf("\n%d\n", ans);
        printf("%d", first + 1);
        for (int i = Next[first][0], j = 1; j < n; i = Next[i][j], j++) printf(" %d", i + 1);
        printf("\n%d\n", ans);
    }
    return 0;
}