#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;
 
const int maxn = 1e5+7;
const double eps = 1e-10;
typedef long long LL;
int dcmp(double a,double b){
    if (fabs(a-b) < eps) return 0;
    if (a > b) return 1;
    return -1;
}
 
int n;
struct Node{
    int l,r;
    void read(){
        scanf("%d %d",&l, &r);
    }
    bool operator < (const Node& rhs) const {
        return r < rhs.r || (r == rhs.r && l < rhs.l);
    }
}p[maxn];
int gcd(int a,int b){
    return !b? a : gcd(b,a%b);
}
 
double mid;
 
bool solve(){
    double la = -1.0;
    for (int i = 0; i < n; ++i){
        if ( dcmp(p[i].l,la) >= 0){
            la = p[i].l + mid;
        }
        else {
            if ( (la+mid) > p[i].r ) return false;
            la += mid;
        }
    }
    return true;
}
int main(){
    while(~scanf("%d",&n)){
        int Rr=0x3f3f3f3f;
        for (int i = 0; i < n; ++i) {
            p[i].read();
            if (p[i].r - p[i].l < Rr) Rr = p[i].r - p[i].l;
        }
        sort(p,p+n);
        double L = 0,R = Rr*1.0;
        while(R-L > eps){
            mid = (L+R)/2.0;
            if (solve()) L = mid;
            else R = mid;
        }
        L = (L+R)/2.0;
        double ans = 1e18;
        int fz;
        int fm;
        for (int i = 1; i <= 100000; ++i){
            int j = floor(i*L);
            if (dcmp( fabs((j*1.0)/i-L) , ans) == -1) {
                ans = fabs((j*1.0)/i - L);
                fz = j;
                fm = i;
            }
            j = ceil(i*L);
 
            if (dcmp( fabs((j*1.0)/i-L) , ans) == -1) {
                ans = fabs((j*1.0)/i - L);
                fz = j;
                fm = i;
            }
        }
        int g = gcd(fz,fm);
        fz /= g;
        fm /= g;
        printf("%d/%d\n",fz,fm);
    }
    return 0;
}
 
 
/**
3
2 6
1 4
8 12
**/