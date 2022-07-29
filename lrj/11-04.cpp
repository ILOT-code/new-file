#include<cstdio>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

const int maxn = 25 + 5;
int n, m, kase;
int vis[maxn], d[maxn][maxn];

vector<string> names;
int ID(const string& s) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i] == s) return i;
    names.push_back(s);
    return names.size() - 1;
}

void print(int u) {
    vis[u] = 1;
    printf("%s", names[u].c_str());
    for (int v = 0; v < n; ++v)
        if (!vis[v] && d[u][v] && d[v][u]) {
            printf(", %s", names[v].c_str());
            vis[v] = 1;
        }
    printf("\n");
}
int main() {
    char s1[100], s2[100];
    while (~scanf("%d%d", &n, &m) && n) {
        names.clear();
        memset(d, 0, sizeof(d));
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; ++i) d[i][i] = 1;
        while (m--) {
            scanf("%s%s", s1, s2);
            d[ID(s1)][ID(s2)] = 1;
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    d[i][j] |= d[i][k] && d[k][j];
        if (kase > 0) printf("\n");
        printf("Calling circles for data set %d:\n", ++kase);
        for (int i = 0; i < n; ++i)
            if (!vis[i]) print(i);
    }
    return 0;
}