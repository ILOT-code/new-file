//所谓语法S->A,可以看成S本身是一个大的串，它可以变成A+空串。
//对于Abca来说，它可以分为A+bca,Ab+ca,Abc+a以及一个空串加另一部分。
//不管怎样，一个形如ABC的大串，总可以分为第一个符号加后面符号串的形式，不必考虑其它分法，
//因为在len确定时，这种分法一定可以找到最优解，因为假如分法A'B'找到了一个最优解，则上面的分法中必然也能找到这个解。
//接下来考虑同层之间的状态转移。设不考虑同层时已找到所有符号在len下的值,排好序。
//设有dp[i][len],dp[j][len],i<j.它们之间可以相互转移，
//那么显然就是dp[j][len]=dp[i][len]就可以了，因为这个情况一定存在，且设更优值存在会有矛盾。
//另外，细节上的处理特别多。
#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
using namespace std;

const int maxn = 50 + 5;
const int maxlen = 20 + 5;
const int maxs = 50 * 20 + 52 + 5;

int n, L, ns;
string rule[maxn], sym[maxs];
int head[maxs], tail[maxs];
string dp[maxs][maxlen];

struct Transform {
    int target, empty;
    Transform(int t, int e): target(t), empty(e) {}
};
vector<Transform> tr[maxs];
map<string, int> sym2id;
int ID(const string &s) {
    if (!sym2id.count(s)) {
        sym[ns] = s;
        sym2id[s] = ns++;
    }
    return sym2id[s];
}

string min(const string &s1, const string &s2) {
    if (s1 == "-") return s2;
    return s1 < s2 ? s1 : s2;
}

bool is_lower(int i, int j) {
    if (sym[i].length() != j) return false;
    for (int k = 0; k < j; ++k)
        if (!(sym[i][k] >= 'a' && sym[i][k] <= 'z')) return false;
    return true;
}

void add_edge(const string &s) {
    int len = s.length();
    int id = ID(s);
    if (len < 2) return;
    int h = ID(s.substr(0, 1));
    int t = ID(s.substr(1));
    tr[h].push_back(Transform(id, t));
    tr[t].push_back(Transform(id, h));
    head[id] = h;
    tail[id] = t;
}

struct Node {
    int x;
    string s;
    Node(int x, string s): x(x), s(s) {}
    bool operator < (const Node &rhs) const {
        return s > rhs.s;
    }
};
bool vis[maxs];
void search(int len) {
    memset(vis, 0, sizeof(vis));
    priority_queue<Node>q;
    for (int i = 0; i < ns; ++i)
        if (dp[i][len] != "-") q.push(Node(i, dp[i][len]));

    while (!q.empty()) {
        Node u = q.top(); q.pop();
        int x = u.x;
        string s = u.s;
        if (vis[x]) continue;
        vis[x] = 1;
        for (int i = 0; i < tr[x].size(); ++i) {
            int target = tr[x][i].target;
            int empty = tr[x][i].empty;
            if (dp[empty][0] == "" && (dp[target][len] == "-" || s < dp[target][len])) {
                dp[target][len] = s;
                q.push(Node(target, s));
            }
        }
    }
}

int main() {
    while (cin >> n >> L && n) {
        ns = 0;
        sym2id.clear();
        ID("");
        for (int i = 0; i < maxs; ++i) tr[i].clear();

        for (int i = 0; i < n; ++i) {
            cin >> rule[i];
            int left = ID(rule[i].substr(0, 1));
            int right = ID(rule[i].substr(2));
            tr[right].push_back(Transform(left, 0));
            for (int j = 2; j < rule[i].length(); ++j)
                add_edge(rule[i].substr(j));
        }

        for (int j = 0; j <= L; ++j)
            for (int i = 0; i < ns; ++i)
                if (is_lower(i, j)) dp[i][j] = sym[i];
                else dp[i][j] = "-";

        for (int j = 0; j <= L; ++j) {
            for (int i = 0; i < ns; ++i) {
                if (sym[i].length() < 2) continue;
                for (int k = 1; k < j; ++k)
                    if (dp[head[i]][k] != "-" && dp[tail[i]][j - k] != "-")
                        dp[i][j] = min(dp[i][j], dp[head[i]][k] + dp[tail[i]][j - k]);
            }
            search(j);
        }
        cout << dp[ID("S")][L] << "\n";
    }
    return 0;
}