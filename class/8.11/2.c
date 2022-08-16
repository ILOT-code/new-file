#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void* a, const void* b) {
	return strcmp((char*)a, (char*)b);
}
int main() {
	char s[20][20];
	int cnt = -1, i = 0;
	for (i = 0; ; ++i) {
		gets(s[i]);
		cnt++;
		if (!s[i][0]) break;
	}
	qsort(s, cnt, sizeof(s[0]), cmp);
	for (i = 0; i < cnt; ++i) puts(s[i]);
	return 0;
}