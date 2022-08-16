#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int transform(char *s) {
	int res = 0;
	while (*s != 0) res = res * 10 + *s++ - '0';
	return res;
}
int trans(char *s) {
	if (*s == '+') return transform(s + 1);
	else if (*s == '-') return 0 - transform(s + 1);
	else return transform(s);
}
void change(char* s, int old, int now) {
	int i;
	if (now >= old)
		for (i = old; i < now; ++i) s[i] = s[i + 1];
	else
		for (i = old; i > now; --i) s[i] = s[i - 1];
	s[now] = '.';
}
int main() {
	char s[100], s1[100];
	int point, newpoint;
	gets(s);
	int i, j;
	for (i = 0; i < strlen(s); ++i) {
		if (s[i] == '.') point = i;
		if (s[i] == 'e') {
			newpoint = point + trans(s + i + 1);
			for (j = i; j < 100; ++j) s1[j] = '0';
			break;
		}
		s1[i] = s[i];
	}
	if (newpoint >= 0) {
		change(s1, point, newpoint);
		if (newpoint == 0) printf("0");
		for (i = 0; i < newpoint; ++i) printf("%c", s1[i]);
		printf(".");
		for (i = 1; i <= 6; ++i) printf("%c", s1[newpoint + i]);
	}
	else {
		printf("0.");
		int t = 0;
		for (i = 1; i <= 6; ++i) {
			if (newpoint - 1 + i < 0) printf("0");
			else {
				if (s1[newpoint - 1 + i] == '.') t = 1;
				printf("%c", s1[i + newpoint - 1 + t]);
			}
		}
	}
	return 0;
}