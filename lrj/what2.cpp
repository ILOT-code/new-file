//代码里的register均可省去，是用于优化的
#include <bits/stdc++.h>
using namespace std;
pair < int, int > ans[1000001];//定义pair来存答案
int n, q[1000001], m, z; //z是答案总数
string s;
bool vis[1000001], f[1000001];//vis是用来判断是否选过这个人，f数组表示是男是女(男是true，女是false)

struct node
{
	int x, y, z;//x为其中一个舞者的编号，y为另一个，z为舞技之差
	friend bool operator < (node a, node b)
	{
		if (a.z == b.z)
		{
			return a.x > b.x;//priority_queue默认大根堆，要反过来写
		}
		else
		{
			return a.z > b.z;//同理
		}
	}
};//不用定义结构体数组
priority_queue < node, vector < node > > pru;//加不加vector都一样，加能更快一些
int main()
{
	scanf("%d", &n);
	cin >> s;
	for (register int i = 0; i < n; ++i)
	{
		if (s[i] == 'B') //用f数组表示男女
		{
			f[i + 1] = true;//要加一(string是从0 ~ n - 1的)
		}
		else//不是男就是女
		{
			f[i + 1] = false;
		}
		m += f[i + 1];
	}
	for (register int i = 1; i <= n; ++i)
	{
		scanf("%d", &q[i]);
	}
	for (register int i = 1; i < n; ++i)
	{
		if (f[i] != f[i + 1]) //不能男和男跳舞，女和女跳舞
		{
			pru.push((node) {i, i + 1, abs(q[i] - q[i + 1])/*要加abs*/}); //可以把它们强制转化到一个结构体里
		}
	}
	printf("%d\n", min(n, n - m));
	while (!pru.empty())
	{
		int x = pru.top().x;//取出第一个人来
		int y = pru.top().y;//取出第二个人来
		pru.pop();//pop掉
		if (!vis[x] && !vis[y]) //不能有一个人跳过舞了
		{
			vis[x] = true;//改成跳过了
			vis[y] = true;
			ans[++z].first = x;//存答案
			ans[z].second = y;//z只加一遍
			//再找一对儿相邻的入队
			//x向左边，y向右边(因为x小，y大)
			while (x > 0 && vis[x]) //跳过了或小于零都不行
			{
				--x;//往左边
			}
			while (y <= n && vis[y]) //跳过了或大于n都不行
			{
				++y;//往右边
			}
			if (x > 0 && y <= n/*有点多余*/ && f[x] != f[y]) //不能男和男或女和女啊
			{
				pru.push((node) {x, y, abs(q[x] - q[y])}); //强制转化成结构体再入队
			}
		}
	}

	for (register int i = 1; i <= z; ++i)
	{
		printf("%d %d\n", ans[i].first, ans[i].second);//输出舞者
	}
	return 0;
}