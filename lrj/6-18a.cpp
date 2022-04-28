#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 50;
const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};
int tu[maxn][maxn][maxn];
int vol;
bool inside(int i, int j, int k) {
    return i >= 0 && i < maxn && j >= 0 && j < maxn && k >= 0 && k < maxn;
}
void solve1(int x, int y, int z) {
    if (!inside(x, y, z)) return;
    if (tu[x][y][z])    return;
    vol++;
    tu[x][y][z] = -1;
    printf("%d", vol);
    for (int i = 0; i < 6; ++i)
        solve1(x + dx[i], y + dy[i], z + dz[i]);
}
int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        int x0, y0, z0, x, y, z;
        scanf("%d%d%d%d%d%d", &x0, &y0, &z0, &x, &y, &z);
        for (int i = x0; i < x0 + x; ++i)
            for (int j = y0; j < y0 + y; ++j)
                for (int k = z0; k < z0 + z; ++k)
                    tu[i][j][k] = 1;
    }
    solve1(0, 0, 0);
    printf("%d", maxn * maxn * maxn - vol);
    return 0;

}
