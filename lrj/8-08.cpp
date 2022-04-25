#include<cstdio>
#include<set>
using namespace std;

const int maxn = 200000 + 5;
int n, ans, a[maxn], f[maxn], g[maxn];

struct Candidate{
    int a, g;
    Candidate(int x, int y):a(x), g(y) {}
    bool operator<(const Candidate &rhs) const{
        return a < rhs.a;
    }
};
set<Candidate> s;

void init() {
    g[0] = 1;
    for(int i = 1; i < n; ++i)
        if(a[i] > a[i-1]) g[i] = 1+g[i-1];
        else g[i] = 1;
    f[n-1] = 1;
    for(int i = n-2; i >= 0; --i)
        if(a[i] < a[i+1]) f[i] = 1+f[i+1];
        else f[i] = 1;
}

void solve() {
    s.clear();
    s.insert(Candidate(a[0], g[0]));
    ans = 1;
    for(int i = 1; i < n; ++i){
        Candidate c(a[i], g[i]);
        set<Candidate>::iterator it = s.lower_bound(c);
        bool keep = true;
        if(it != s.begin()){
            Candidate last = *(--it);
            int len = f[i]+last.g;
            ans = max(len, ans);
            if(c.g <= last.g) keep = false;
        }
        if(keep){
            s.erase(c);
            s.insert(c);
            it = s.find(c);
            it++;
            while(it != s.end() && it->g <= c.g) s.erase(it++);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        if(n == 1) { printf("1\n"); continue; }
        init();
        solve();
        printf("%d\n", ans);
    }
    return 0;
}