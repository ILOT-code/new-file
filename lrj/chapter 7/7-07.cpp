//暴力枚举所有的树
//位运算
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 6;
int vis[1 << maxn];
int n;
double r, w[maxn], sum[1 << maxn];
struct Tree {
    double L, R;
    Tree(): L(0), R(0) {}
};
vector<Tree> tree[1 << maxn];
void dfs(int subset) {
    if (vis[subset]) return;
    vis[subset] = 1;
    bool have_child = false;
    for (int left = (subset - 1)&subset; left; left = (left - 1)&subset) {
        int right = subset ^ left;
        have_child = true;
        double d1 = sum[right] / sum[subset];
        double d2 = sum[left] / sum[subset];
        dfs(left); dfs(right);
        for (int i = 0; i < tree[left].size(); ++i)
            for (int j = 0; j < tree[right].size(); ++j) {
                Tree t;
                t.L = max(tree[left][i].L + d1, tree[right][j].L - d2);
                t.R = max(tree[right][j].R + d2, tree[left][i].R - d1);
                if (t.L + t.R < r)  tree[subset].push_back(t);
            }
    }
    if (!have_child) tree[subset].push_back(Tree());
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lf%d", &r, &n);
        for (int i = 0; i < n; ++i)    scanf("%lf", &w[i]);
        for (int i = 0; i < (1 << n); ++i) {
            sum[i] = 0;
            tree[i].clear();
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j))
                    sum[i] += w[j];
            }
        }
        memset(vis, 0, sizeof(vis));
        int root = (1 << n) - 1;
        dfs(root);
        double ans = -1;
        for (int i = 0; i < tree[root].size(); ++i)
            ans = max(ans, tree[root][i].L + tree[root][i].R);
        printf("%.10lf\n", ans);
    }
    return 0;
}