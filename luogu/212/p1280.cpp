#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
const int INF = 0x3f3f3f3f;

int n, k, d[maxn];
struct Event {
	int sta, dur;
	Event(int sta = 0, int dur = 0): sta(sta), dur(dur) {}
	bool operator<(const Event& rhs) const {
		return sta < rhs.sta;
	}
} e[maxn];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; ++i)
		scanf("%d%d", &e[i].sta, &e[i].dur);

	sort(e, e + k);
	d[n] = 0;
	for (int i = n; i >= 1; --i) {
		int left = lower_bound(e, e + k, Event(i)) - e;
		int right = upper_bound(e, e + k, Event(i)) - e;
		int t = right - left;
		if (t == 0) d[i] = d[i + 1] + 1;
		else {
			for (int j = left; j < right; ++j)
				d[i] = max(d[i], d[i + e[j].dur]);
		}
	}
	printf("%d\n", d[1]);
}
