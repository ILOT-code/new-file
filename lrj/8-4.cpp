#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 5000 + 5;
int n, x1[maxn], x2[maxn], y1[maxn], y2[maxn], x[maxn], y[maxn];

bool solve(int *a, int *b, int *c) {
    fill(c, c + n, -1);
    for (int col = 1; col <= n; ++col) {
        int temp = -1, minb = n + 1;
        for (int i = 0; i < n; ++i)
            if (c[i] < 0 && a[i] <= col && b[i] < minb) {temp = i, minb = b[i];}
        if (temp < 0 || minb < col) return false;
        c[temp] = col;
    }
    return true;
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++i)
            scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
        if (solve(x1, x2, x) && solve(y1, y2, y))
            for (int i = 0; i < n; ++i) printf("%d %d\n", x[i], y[i]);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}

