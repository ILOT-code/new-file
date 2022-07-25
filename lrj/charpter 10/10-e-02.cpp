//6个方向对应+x,-x,+y,-y,+x +y,-x -y.
//因此，若dx,dy同号，则为max(|dx|,|dy|),否则为|x|+|y|.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
struct point {
    int x, y;
    point(int x = 0, int y = 0): x(x), y(y) {}
    point operator - (const point& c) { return point(x - c.x, y - c.y); }
};

point pos (int n) {
    if (n == 1) return point(0, 0);
    int d;
    for (d = 1, n--; n > d * 6; ++d) n -= d * 6;

    if (n <= 1 * d) return point(-n, -d);
    if (n <= 2 * d) return point(-d, -d + n - d);
    if (n <= 3 * d) return point(-d + n - 2 * d, n - 2 * d);
    if (n <= 4 * d) return point(n - 3 * d, d);
    if (n <= 5 * d) return point(d, d - (n - 4 * d));
    else return point(d - (n - 5 * d), -(n - 5 * d));
}

int main () {
    int n, m, ans;
    while (~scanf("%d%d", &n, &m) && n && m) {
        point d = pos(n) - pos(m);
        if (d.x * d.y >= 0) ans = max(abs(d.x), abs(d.y));
        else ans = abs(d.x) + abs(d.y);
        printf("The distance between cells %d and %d is %d.\n", n, m, ans);
    }
    return 0;
}