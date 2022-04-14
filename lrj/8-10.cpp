#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 500 + 10;
int n, k, a[maxn], s[maxn], flag[maxn];

int P(int x) {
    int cnt = 0;
    int i = 1, j = 1;
    while (j <= n) {
        while (j <= n && s[j] - s[i - 1] <= x)  ++j;
        i = j; cnt++;
    }
    return cnt <= k;
}

void print_ans(int x) {
    memset(flag, 0, sizeof(flag));
    int i = n, j = n;
    while (j >= 1) {
        while (j >= 1 && s[i] - s[j - 1] <= x) --j;
        i = j; flag[i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", a[i]);
        if (flag[i]) printf("| ");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        int x0 = 0, y0 = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            x0 = max(x0, a[i]); y0 += a[i];
        }
        for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
        while (x0 < y0) {
            int m = x0 + (y0 - x0) / 2;
            if (P(m)) y0 = m;
            else x0 = m + 1;
        }
        print_ans(x0);
    }
    return 0;
}
