//状态转移如果只涉及前后两个状态，可以只开两个空间，用异或式减小空间消耗。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;
const int INF = 1<<30;
char p[maxn], q[maxn];
int sp[26], sq[26], ep[26], eq[26];
int d[2][maxn], c[2][maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", p + 1, q + 1);
        int n = strlen(p + 1);
        int m = strlen(q + 1);
        for (int i = 1; i <= n; i++) p[i] -= 'A';
        for (int i = 1; i <= m; i++) q[i] -= 'A';

        for (int i = 0; i < 26; i++) { sp[i] = sq[i] = INF; ep[i] = eq[i] = 0; }
        for (int i = 1; i <= n; i++) {
            if (sp[p[i]] == INF) sp[p[i]] = i;
            ep[p[i]] = i;
        }
        for (int i = 1; i <= m; i++) {
            if (sq[q[i]] == INF) sq[q[i]] = i;
            eq[q[i]] = i;
        }

        int t = 0;
        memset(c, 0, sizeof(c));
        memset(d, 0, sizeof(d));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (!i && !j) continue;
                int v1 = INF, v2 = INF;
                if (i) v1 = d[t ^ 1][j] + c[t ^ 1][j];
                if (j) v2 = d[t][j - 1] + c[t][j - 1];
                d[t][j] = min(v1, v2);
                if (j) {
                    c[t][j] = c[t][j - 1];
                    if (sq[q[j]] == j && sp[q[j]] > i) c[t][j]++;
                    if (eq[q[j]] == j && ep[q[j]] <= i) c[t][j]--;
                }
                else {
                    c[t][j] = c[t ^ 1][j];
                    if (sp[p[i]] == i) c[t][j]++;
                    if (ep[p[i]] == i && eq[p[i]] <= j) c[t][j]--;
                }
            }
            t = t ^ 1;
        }
        printf("%d\n", d[t ^ 1][m]);
    }
    return 0;
}

