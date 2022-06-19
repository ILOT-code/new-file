#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using  namespace std;
const int maxn = 50 + 5;
const int maxc = 1000 + 5;
const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};
int n, x0[maxn], y0[maxn], z0[maxn], x1[maxn], y1[maxn], z1[maxn];
int nx, ny, nz;
int xs[2 * maxn], ys[2 * maxn], zs[2 * maxn];
int color[maxn * 2][maxn * 2][maxn * 2];
struct Cell {
    int x, y, z;
    Cell(int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
    bool valid() const {
        return x >= 0 && x < nx - 1 && y >= 0 && y < ny - 1 && z >= 0 && z < nz - 1;
    }
    bool solid() const {
        return color[x][y][z] == 1;
    }
    bool getVis() const {
        return color[x][y][z] == 2;
    }
    void setVis() const {
        color[x][y][z] = 2;
    }
    Cell neighbor(int i) const {
        return Cell(x + dx[i], y + dy[i], z + dz[i]);
    }
    int volume() const {
        return (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
    }
    int area(int i) const {
        if (dx[i])  return (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
        if (dy[i])  return (xs[x + 1] - xs[x]) * (zs[z + 1] - zs[z]);
        else       return (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]);
    }

};
void discretize(int* x, int& n) {
    sort(x, x + n);
    n = unique(x, x + n) - x;
}
int ID(int *x, int n, int x0) {
    return lower_bound(x, x + n, x0) - x;
}
void floodfill(int &v, int &s) {
    v = s = 0;
    Cell c;
    c.setVis();
    queue<Cell> q;
    q.push(c);
    while (!q.empty()) {
        Cell c = q.front(); q.pop();
        v += c.volume();
        for (int i = 0; i < 6; ++i) {
            Cell d = c.neighbor(i);
            if (!d.valid()) continue;
            if (d.solid())  s += d.area(i);
            else if (!d.getVis()) {
                d.setVis();
                q.push(d);
            }
        }
    }
    v = maxc * maxc * maxc - v;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        xs[0] = ys[0] = zs[0] = 0;
        xs[1] = ys[1] = zs[1] = maxc;
        nx = ny = nz = 2;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d%d%d", &x0[i], &y0[i], &z0[i], &x1[i], &y1[i], &z1[i]);
            x1[i] += x0[i]; y1[i] += y0[i]; z1[i] += z0[i];
            xs[nx++] = x0[i]; xs[nx++] = x1[i];
            ys[ny++] = y0[i]; ys[ny++] = y1[i];
            zs[nz++] = z0[i]; zs[nz++] = z1[i];
        }
        discretize(xs, nx);
        discretize(ys, ny);
        discretize(zs, nz);
        memset(color, 0, sizeof(color));
        for (int i = 0; i < n; ++i) {
            int X1 = ID(xs, nx, x0[i]); int X2 = ID(xs, nx, x1[i]);
            int Y1 = ID(ys, ny, y0[i]); int Y2 = ID(ys, ny, y1[i]);
            int Z1 = ID(zs, nz, z0[i]); int Z2 = ID(zs, nz, z1[i]);
            for (int i = X1; i < X2; ++i)
                for (int j = Y1; j < Y2; ++j)
                    for (int k = Z1; k < Z2; ++k)
                        color[i][j][k] = 1;
        }
        int v, s;
        floodfill(v, s);
        printf("%d %d", v, s);
    }
    return 0;
}
