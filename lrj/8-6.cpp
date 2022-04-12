#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 1000+5;
struct Point{
    int x, y;
    double rad;
    bool operator<(const Point &a) const{
        return rad<a.rad;
    }
}op[maxn],p[maxn];
int n, color[maxn];
bool Left(Point a, Point b){
    return a.x*b.y>=a.y*b.x;
}

int solve(){
    if(n<=2) return n;
    int ans = 0;
    for(int i = 0; i < n; ++i){
        int k=0;
        for(int j = 0; j < n; ++j)
            if(j!=i){
                p[k].x=op[j].x - op[i].x;
                p[k].y=op[j].y - op[i].y;
                if(color[j]) { p[k].x = -p[k].x; p[k].y = -p[k].y; }
                p[k].rad=atan2(p[k].y, p[k].x);
                k++;
            }

        sort(p, p+k);
        int L = 0, R = 0, cnt = 2;
        while(L < k){
            if(L == R) { R=(R+1)%k; cnt = 3; };
            while(Left(p[L], p[R]) && R!=L) { R=(R+1)%k; cnt++; }
            L++;
            cnt--;
            ans=max(ans, cnt);
        }
    }
    return ans;
}

int main() {
    while(scanf("%d", &n) == 1 && n){
        for(int i = 0; i < n; ++i)
            scanf("%d%d%d", &op[i].x, &op[i].y, &color[i]);
        printf("%d\n", solve());
    }
    return 0;
}