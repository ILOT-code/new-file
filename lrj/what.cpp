//	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
//	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 300;

void test_1() {
	int dp[N][N];
	int dp_1[10][10];
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) printf("%d ", dp_1[i][j]);
		printf("\n");
	}
}
void test_2() {
	int dp_2[10][10];
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) printf("%d ", dp_2[i][j]);
		printf("\n");
	}
}
int main() {
	vector<int> a, b;
	a.push_back(0); a.push_back(1);
	b = a;
	for(int i = 0; i < b.size(); ++i)
		printf("%d", b[i]);

	return 0;

}