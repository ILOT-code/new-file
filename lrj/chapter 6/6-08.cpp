#include <iostream>
#include <string>
#include <sstream>
using namespace std;
const int maxd = 10000 + 10;
int n, best, best_sum;
int in[maxd], post[maxd], lch[maxd], rch[maxd];
bool read_list(int *a) {
    string line;
    if (!getline(cin, line)) return false;
    stringstream ss(line);
    n = 0;
    int x;
    while (ss >> x) a[n++] = x;
    return 1;
}
int build(int L1, int R1, int L2, int R2) {
    if (L1 > R1) return 0;
    int root = post[R2];
    int p = L1;
    while (in[p] != root) p++;
    int cnt = p - L1;
    lch[root] = build(L1, p - 1, L2, L2 + cnt - 1);
    rch[root] = build(p + 1, R1, L2 + cnt, R2 - 1);
    return root;
}
void dfs(int root, int sum) {
    sum += root;
    if (!lch[root] && !rch[root]) {
        if (sum < best_sum || (sum == best_sum && root < best)) {
            best = root; best_sum = sum;
        }
    }
    if (lch[root]) dfs(lch[root], sum);
    if (rch[root]) dfs(rch[root], sum);
}
int main() {
    while (read_list(in)) {
        read_list(post);
        build(0, n - 1, 0, n - 1);
        best_sum = 1000000000;
        dfs(post[n - 1], 0);
        cout << best << endl;
    }
    return 0;
}