#include<stdio.h>
#include<stdlib.h>

int cmp(const void* a, const void* b) {
	if (((int*)a)[1] == ((int*)b)[1]) return ((int*)a)[0] - ((int*)b)[0];
	return ((int*)a)[1] - ((int*)b)[1];
}

int main() {
	int noze1[100][3], noze2[100][3], cnt1, cnt2;
	int i, j, p, q;
	scanf("%d", &cnt1);
	for (i = 0; i < cnt1; ++i)
		for (j = 0; j < 3; ++j) scanf("%d", &noze1[i][j]);
	scanf("%d", &cnt2);
	for (i = 0; i < cnt2; ++i)
		for (j = 0; j < 3; ++j) scanf("%d", &noze2[i][j]);

	qsort(noze2, cnt2, sizeof(int) * 3, cmp);
	for (i = 0, j = 0; i < cnt1; i = j + 1, j = i) {
		while (j + 1 < cnt1 && noze1[j][0] == noze1[j + 1][0]) j++;
		for (p = 0, q = 0; p < cnt2; p = q + 1, q = p) {
			while (q + 1 < cnt2 && noze2[q][1] == noze2[q + 1][1]) q++;
			int res = 0, f = i, r = p;
			while (f <= j && r <= q) {
				while (r <= q && noze2[r][0] < noze1[f][1]) r++;
				if (r <= q && noze2[r][0] == noze1[f][1]) res += noze2[r][2] * noze1[f][2];
				f++;
			}
			if (res) printf("%d %d %d\n", noze1[i][0], noze2[p][1], res);
		}
	}
	return 0;
}