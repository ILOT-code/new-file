#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100 + 10;
int d[maxn][4][4][3], action[maxn][4][4][3];
char seq[maxn], pos[256], footch[] = ".LR";

int cost(int a, int ta) {
    if (a == ta) return 3;
    if (a + ta == 3) return 7;
    return 5;
}
int energy(int i, int a, int b, int s, int f, int t, int &ta, int &tb) {
    ta = a; tb = b;
    if (f == 1) ta = t;
    if (f == 2) tb = t;
    if ((ta == tb) || (ta == 2 && tb == 1)) return -1;
    if ((a == 2 && tb != b) || (b == 1 && ta != a)) return -1;
    if (f == 0) return 0;
    if (s != f) return 1;
    if (f == 1) return cost(a, ta);
    return cost(b, tb);
}

void update(int i, int a, int b, int s, int f, int t) {
    int ta, tb;
    int e = energy(i, a, b, s, f, t, ta, tb);
    if (e < 0) return;

    int &temp = d[i][a][b][s];
    if (temp > e + d[i + 1][ta][tb][f]) {
        temp = e + d[i + 1][ta][tb][f];
        action[i][a][b][s] = 4 * f + t;
    }
}

int main() {
    pos['U'] = 0; pos['L'] = 1; pos['R'] = 2; pos['D'] = 3;
    while (~scanf("%s", seq)) {
        if (seq[0] == '#') break;
        int n = strlen(seq);
        memset(d, 0, sizeof(d));
        for (int i = n - 1; i >= 0; --i)
            for (int a = 0; a < 4; ++a)
                for (int b = 0; b < 4; ++b)if (a != b && !(a == 2 && b == 1))
                        for (int s = 0; s < 3; ++s) {
                            d[i][a][b][s] = 10 * n;
                            if (seq[i] == '.') {
                                update(i, a, b, s, 0, 0);
                                for (int t = 0; t < 4; ++t) {
                                    update(i, a, b, s, 1, t);
                                    update(i, a, b, s, 2, t);
                                }
                            }
                            else {
                                update(i, a, b, s, 1, pos[seq[i]]);
                                update(i, a, b, s, 2, pos[seq[i]]);
                            }
                        }
        int a = 1, b = 2, s = 0;
        for (int i = 0; i < n; ++i) {
            int f = action[i][a][b][s] / 4;
            int t = action[i][a][b][s] % 4;
            printf("%c", footch[f]);
            s = f;
            if (f == 1) a = t;
            if (f == 2) b = t;
        }
        printf("\n");
    }
    return 0;
}