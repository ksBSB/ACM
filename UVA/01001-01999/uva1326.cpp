#include <stdio.h>
#include <string.h>

const int N = 105;

int n, k[N], c[N], v[N], ans;

int handle(char* s) {
	int len = strlen(s), k = 0;
	for (int i = 0; i < len; i++)
		k = k ^ (1<<(s[i]-'A'));
	return k;
}

void init () {
	ans = 0;
	memset(v, 0, sizeof(v));
	memset(c, 0, sizeof(c));

	char word[N];
	for (int i = 0; i < n; i++) {
		scanf("%s", word);
		k[i] = handle(word);
	}
}

void dfs (int d, int s, int cnt) {
	if (d >= n) {
		if (s == 0 && cnt > ans) {
			memcpy(v, c, sizeof(c));
			ans = cnt;
		}
		return;
	}

	c[d] = 0;
	dfs (d + 1, s, cnt);
	c[d] = 1;
	dfs (d + 1, s ^ k[d], cnt + 1);
	c[d] = 0;
}

void put () {
	printf("%d\n", ans);
	int x = 0;
	for (int i = 0; i < 24; i++) if (v[i]) {
		if (x++) printf(" ");
		printf("%d", i + 1);
	}
	printf("\n");
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		dfs(0, 0, 0);
		put();
	}
	return 0;
}
