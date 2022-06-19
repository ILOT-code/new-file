#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct Node
{
    int r, c, dir;
    Node(int r = 0, int c = 0, int dir = 0) : r(r), c(c), dir(dir) {}
};
const int maxn = 10;
const char *dirs = "NESW";
const char *turns = "FLR";
const int dr[] = { -1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
int r0, c0, dir, r1, c1, r2, c2;
int has_edge[maxn][maxn][4][3];
int d[maxn][maxn][4];
Node pre[maxn][maxn][4];
int dir_id(char c) {
    return strchr(dirs, c) - dirs;
}
int turn_id(char c) {
    return strchr(turns, c) - turns;
}
bool inside(Node u) {
    return u.r >= 1 && u.r <= 9 && u.c >= 1 && u.c <= 9;
}
Node walk(Node u, int turn) {
    int dir = u.dir;
    if (turn == 1) dir = (dir + 3) % 4;
    if (turn == 2) dir = (dir + 1) % 4;
    return Node(u.r + dr[dir], u.c + dc[dir], dir);
}
bool read_list() {
    char s1[99], s2[2];
    if (scanf("%s%d%d%s%d%d", s1, &r0, &c0, s2, &r2, &c2) != 6) return false;
    dir = dir_id(s2[0]);
    r1 = r0 + dr[dir];
    c1 = c0 + dc[dir];
    memset(has_edge, 0, sizeof(has_edge));
    for (;;) {
        int r, c;
        scanf("%d", &r);
        if (r == 0) break;
        scanf("%d", &c);
        for (;;) {
            scanf("%s", s1);
            if (s1[0] == '*') break;
            for (int i = 1; i < strlen(s1); i++)
                has_edge[r][c][dir_id(s1[0])][turn_id(s1[i])] = 1;
        }
    }
    return true;
}
void print_ans(Node u) {
    vector<Node> nodes;
    for (;;) {
        nodes.push_back(u);
        if (u.c == c1 && u.r == r1 && u.dir == dir) break;
        u = pre[u.r][u.c][u.dir];
    }
    nodes.push_back(Node(r0, c0, dir));
    int cnt = 0;
    for (int i = nodes.size() - 1; i >= 0; --i) {
        if (cnt % 10 == 0) printf("    ");
        printf("  (%d,%d)", nodes[i].r, nodes[i].c);
        if (++cnt % 10 == 0)   printf("\n");
    }
}
void solve() {
    memset(d, 0, sizeof(d));
    queue<Node> p;
    Node u(r1, c1, dir);
    p.push(u);
    d[r1][c1][dir] = 1;
    while (!p.empty()) {
        Node u = p.front(); p.pop();
        if (u.r == r2 && u.c == c2) {print_ans(u); return;}
        for (int i = 0; i < 3; ++i) {
            Node v = walk(u, i);
            if (inside(v) && d[v.r][v.c][v.dir] == 0 && has_edge[u.r][u.c][u.dir][i]) {
                p.push(v);
                d[v.r][v.c][v.dir] = 1;
                pre[v.r][v.c][v.dir] = u;
            }
        }
    }
    printf("No answer!\n");
}
int main() {
    while (read_list()) {
        solve();
    }
    return 0;
}