//把这个十进制数分为左右两个数字,左方高数位，右方低数位。比如1234分为12和34。
//d[i][j]表示，用不超过i根火柴拼成低位，且高位数字除m余j，低位能够拼成的最大长度。
//p[i][j]表示在d[i][j]最大的情况下低位第一个数字的最大值。
//这种状态转移很巧妙，不过它的效率并不如9-22.
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100 + 5;
const int maxm = 3000 + 5;
int n, m, d[maxn][maxm], p[maxn][maxm];
int c[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main() {
    int kase = 0;
    while (~scanf("%d%d", &n, &m) && n) {
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j < m; ++j) {
                int& ans = d[i][j];
                ans = p[i][j] = -1;
                if (j == 0) ans = 0;
                for (int k = 9; k >= 0; --k)
                    if (i >= c[k]) {
                        int t = d[i - c[k]][(j * 10 + k) % m];
                        if (t >= 0 && t + 1 > ans) {
                            ans = t + 1;
                            p[i][j] = k;
                        }
                    }
            }
        printf("Case %d: ", ++kase);
        if (p[n][0] < 0) printf("-1");
        else if(p[n][0] == 0) printf("0");
        else {
            int i = n, j = 0;
            for (int k = p[i][j]; k >= 0; k = p[i][j]) {
                printf("%d", k);
                i -= c[k];
                j = (j * 10 + k) % m;
            }
        }
        printf("\n");
    }
    return 0;
}
