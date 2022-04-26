#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <bitset> 
#include <cassert> 
#include <cmath>
#include <functional>
 
using namespace std;
 
const int maxn = 1 << 15;
int A[maxn];
 
// 0,1,2,3分别是上下左右
int trans[] = { 2, 3, 1, 0 };
 
map<int, set< pair<int, int> > > P;
 
void build(int n)
{
    int m = 1;
    A[0] = 3;
    for (int i = 1; i <= n; i++) {
        for (int j = m - 1, k = m; j >= 0; j--, k++) { // 算出下一次展开的位置
            A[k] = trans[A[j]];
        }
        m <<= 1;
    }
    int x = -1, y = 0, px = 0, py = 0;
    P.clear();
    // 把每个短线的位置计算出来，并放入P中
    for (int i = 0; i < m; i++) {
        if (A[i] == 0) {
            x = px << 1;
            y = py;
            P[y].insert(make_pair(x, 0));
            py++;
        }
        else if (A[i] == 1) {
            x = px << 1;
            y = py - 1;
            P[y].insert(make_pair(x, 1));
            py--;
        }
        else if (A[i] == 2) {
            x = (px << 1) - 1;
            y = py;
            P[y].insert(make_pair(x, 2));
            px--;
        }
        else {
            x = (px << 1) + 1;
            y = py;
            P[y].insert(make_pair(x, 3));
            px++;
        }
    }
}
 
void draw()
{
    // 设置无穷大和无穷小，具体为什么在这篇题解前一篇博文有说明
    int mxy = -0x3f3f3f3f, mnx = 0x3f3f3f3f;
    for (map<int, set< pair<int, int> > >::iterator it = P.begin();
        it != P.end(); it++) {
        mxy = max(mxy, it->first);
        for (set< pair<int, int> >::iterator jt = it->second.begin();
            jt != it->second.end(); jt++) {
            mnx = min(mnx, jt->first);
        }
    }
    // 从最上面一行画起，所以需要反向遍历
    for (map<int, set< pair<int, int> > >::reverse_iterator it = P.rbegin();
        it != P.rend(); it++) {
        int i = mnx;
        for (set<pair<int, int> >::iterator jt = it->second.begin();
            jt != it->second.end(); jt++) {
            while (i < jt->first) {
                cout << ' ';
                i++;
            }
            i++;
            if (jt->second == 0 || jt->second == 1) {
                cout << '|';
            }
            else {
                cout << '_';
            }
        }
        cout << endl;
    }
    cout << '^' << endl;
}
 
int main()
{
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        build(n);
        draw();
    }
 
    return 0;
}