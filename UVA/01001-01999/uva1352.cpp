#include <stdio.h>
#include <string.h>

#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)

const int N = 30;
const int dice[24][6] = {
 {2, 1, 5, 0, 4, 3}, {2, 0, 1, 4, 5, 3}, {2, 4, 0, 5, 1, 3}, {2, 5, 4, 1, 0, 3},
 {4, 2, 5, 0, 3, 1}, {5, 2, 1, 4, 3, 0}, {1, 2, 0, 5, 3, 4}, {0, 2, 4, 1, 3, 5},
 {0, 1, 2, 3, 4, 5}, {4, 0, 2, 3, 5, 1}, {5, 4, 2, 3, 1, 0}, {1, 5, 2, 3, 0, 4},
 {5, 1, 3, 2, 4, 0}, {1, 0, 3, 2, 5, 4}, {0, 4, 3, 2, 1, 5}, {4, 5, 3, 2, 0, 1},
 {1, 3, 5, 0, 2, 4}, {0, 3, 1, 4, 2, 5}, {4, 3, 0, 5, 2, 1}, {5, 3, 4, 1, 2, 0},
 {3, 4, 5, 0, 1, 2}, {3, 5, 1, 4, 0, 2}, {3, 1, 0, 5, 4, 2}, {3, 0, 4, 1, 5, 2},
};

char name[N][N];
int n, ans, cnt, c[N], s[N][N];

int find(char *str) {
	for (int i = 0; i < cnt; i++)
		if (strcmp(name[i], str) == 0) return i;

	strcpy(name[cnt], str);
	return cnt++;
}

void init() {

	ans = N;
	cnt = 0;
	memset(name, 0, sizeof(name));
	memset(c, 0, sizeof(c));

	char str[N];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			scanf("%s", str);
			int id = find(str);
			s[i][j] = id;
		}
	}
}

void judge() {
	int v[N], sum = 0;

	for (int i = 0; i < 6; i++) {
		memset(v, 0, sizeof(v));
		int cur = 0;

		for (int j = 0; j < n; j++) {
			int k = dice[c[j]][i];
			v[s[j][k]]++;
			cur = max(cur, v[s[j][k]]);
		}
		sum += n - cur;
	}
	ans = min(sum, ans);
}

void dfs(int d) {
	if (d >= n) {
		judge();
		return;
	}

	for (c[d] = 0; c[d] < 24; c[d]++)
		dfs(d + 1);
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init();
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
