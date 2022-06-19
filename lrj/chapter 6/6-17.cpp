#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
const int maxn = 200 + 10;
int n;
char buf[maxn][maxn];
void dfs( int r, int c) {
    printf("%c(", buf[r][c]);
    if (buf[r + 1][c] == '|' && r + 1 < n) {
        int left = c;
        while (buf[r + 2][left - 1] == '-' && left - 1 >= 0) left--;
        while (buf[r + 2][left] == '-' && buf[r + 3][left] != 0) {
            if (!isspace(buf[r + 3][left])) dfs(r + 3, left);
            left++;
        }
    }
    printf(")");

}
void solve() {
    n = 0;
    for (;;) {
        fgets(buf[n], maxn, stdin);
        if (buf[n][0] == '#') break;
        n++;
    }
    printf("(");
    if (n) {
        for (int i = 0; i < strlen(buf[0]); ++i)
            if (buf[0][i] != ' ') { dfs(0, i); break;}
    }
    printf(")\n");
}
int main() {
    int T;
    fgets(buf[0], maxn, stdin);
    sscanf(buf[0], "%d", &T);
    while (T--) solve();
    return 0;
}