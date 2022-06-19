#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 70 + 5;
const int maxw = 30;
const int INF = 1 << 30;
int n, dp[2][maxn * maxw][maxn * maxw], sumw[maxn];

struct Book {
    int h, w;
    bool operator < (const Book& rhs) const {
        return h > rhs.h || (h == rhs.h && w > rhs.w);
    }
} books[maxn];

inline void update(int& newstate, int k) {
    if (newstate < 0 || newstate > k) newstate = k;
}

int main () {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d%d", &books[i].h, &books[i].w);
        sort(books, books + n);
        sumw[0] = books[0].w;
        for (int i = 1; i < n; ++i) sumw[i] = sumw[i - 1] + books[i].w;
        int t = 0;
        dp[t][0][0] = 0; //本来dp[0][i][j]需要初始化为-1的，但j，k的限制使得免去了这个步骤。
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j <= sumw[i + 1] - sumw[0]; ++j)
                for (int k = 0; k <= sumw[i + 1] - sumw[0] - j; ++k) dp[t ^ 1][j][k] = -1;
            for (int j = 0; j <= sumw[i] - sumw[0]; ++j)
                for (int k = 0; k <= sumw[i] - sumw[0] - j; ++k) if (dp[t][j][k] != -1) {
                    update(dp[t ^ 1][j][k], dp[t][j][k]);
                    update(dp[t ^ 1][j + books[i + 1].w][k], dp[t][j][k] + (j == 0 ? books[i + 1].h : 0));
                    update(dp[t ^ 1][j][k + books[i + 1].w], dp[t][j][k] + (k == 0 ? books[i + 1].h : 0));
                }
            t ^= 1;
        }
        int ans = INF;
        for (int i = 1; i <= sumw[n - 1] - sumw[0]; ++i)
            for (int j = 1; j <= sumw[n - 1] - sumw[0] - i; ++j)
                if (dp[t][i][j] != -1) ans = min(ans, max(max(i, j), sumw[n - 1] - i - j) * (books[0].h + dp[t][i][j]));
        printf("%d\n", ans);
    }
    return 0;
}
