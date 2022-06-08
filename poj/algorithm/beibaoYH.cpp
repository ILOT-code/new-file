//https://www.luogu.com.cn/problem/U189808
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n, K, P, w, v, p;
int f[2001][15];
int main()
{
	cin >> n >> K >> P;
	memset(f,-1,sizeof(f));
	f[0][0] = 0;
    int ans = 0;
	for(int i=1;i<=n;i++)
	{
		cin >> w >> v >> p;
		for(int j=K-w;j>=0;j--)
            for(int o=P-p;o>=0;o--)
            if(f[j][o]!=-1)
			if(f[j+w][o+p] < f[j][o]+v)
			{
				f[j+w][o+p] = f[j][o] +v;
				ans = max(ans,f[j][o]+v);
			}
	}
	cout << ans;
	return 0;
}
