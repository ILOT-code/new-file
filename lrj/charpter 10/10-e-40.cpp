#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const double eps = 1e-6;
LL n, r, kase, ans;
vector<double> angs;
bool dcmp(double d1, double d2) { return d1 - d2 < -eps;}

int main() {
	while (~scanf("%lld%lld", &n, &r) && n && r) {
		ans = n * (n - 1) * (n - 2) / 6;
		angs.clear();
		for (int i = 0; i < n; ++i) {
			double ang;
			scanf("%lf", &ang);
			angs.push_back(ang);
			angs.push_back(ang + 360);
		}
		sort(angs.begin(), angs.end());
		for (int i = 0; i < n; ++i) {
			auto ait = angs.begin() + i;
			LL m = upper_bound(ait, angs.end(), (*ait) + 180, dcmp) - ait - 1;
			ans -= m * (m - 1) / 2;
		}
		printf("Case %lld: %lld\n", ++kase, ans);
	}
}
