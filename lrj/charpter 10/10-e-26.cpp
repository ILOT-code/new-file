//下面除法若不说明，都是指数学中的除法。
//如果l是偶数，则best=L*L/2,否则是(L*L+1)/2.都可以写作(L*L+1)/2(整除);
//如果n<=best,res=4*n;
//否则，设内部center_best.看成是挖去空格。
//如果remain<=center_best,则每挖一个就增加4,则res=4*(L+remain);
//再否则，考虑L为偶数。
//有n>L*L/2,remain>center_best,这时，还可以挖去外围四条边上的格子，
//每挖一个，就增加2，这样的格子为4*(L/2-1)个。如果remain>center_best+4*(L/2-1)
//由上面的不等式可以得到n只有唯一一个值可以取，此时remain=center_best+4*(L/2-1)+1;
//多出来的这一个可以挖去四个角，不会改变周长。
//n为偶数，由于对称性，只有这一种情况。
//考虑L为奇数。此时n>(L*L+1)/2,remain>center_best,则内部正方形有两种挖法。
//1：内部挖去((L-2)*(L-2)+1)/2,每一个增加4，外围四条边可以挖去4*((L-1)/2-1)，每一个增加2.
//如果remain>((L-2)*(L-2)+1)/2+4*((L-1)/2-1),由不等式可得，remain=((L-2)*(L-2)+1)/2+4*((L-1)/2-1)+1(+2);
//多出来的格子<4,则一定能够在四个角上挖掉。
//2：内部挖去((L-2)*(L-2)-1)/2,每一个增加4，外围四条边可以挖去4*((L-1)/2)，每一个增加2.
//由不等式的关系，得到remain<((L-2)*(L-2)-1)/2+4*((L-1)/2),也就是一定够。
//在remain=((L-2)*(L-2)+1)/2+4*((L-1)/2-1)+2时，情况二比情况一多2。其它情况情况2都<=情况1.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
LL L, N;

int main() {
	while (~scanf("%lld%lld", &L, &N) && L) {
		LL best = (L * L + 1) / 2;
		LL remain = L * L - N;
		LL center_best = ((L - 2) * (L - 2) + 1) / 2;
		LL res;
		if (N <= best) res = 4 * N;
		else if (remain <= center_best) res = 4 * (L + remain);
		else {
			res = 4 * (L + center_best) +
			      2 * min(remain - center_best, 4 * (L / 2 - 1));
			if (L % 2 && remain == center_best + 4 * (L / 2 - 1) + 2) res += 2;
		}
		printf("%lld\n", res);
	}
	return 0;
}