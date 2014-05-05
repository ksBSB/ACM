#include <stdio.h>
#include <string.h>

const int N = 30;
const char T[N][N] = { "XXL", "XL", "L", "M", "S", "XS" };

int n, m, tmp[N];
int size[N][2];

int solve(char *s) {
	for (int i = 0; i < 6; i++)
		if (strcmp(s, T[i]) == 0) return i;
	printf("Wrong!\n");
	return 0;
}

void init(int t) {
	for (int i = 0; i < 6; i++) 
		tmp[i] = t;

	char a[N], b[N];

	for (int i = 0; i < m; i++) {
		scanf("%s%s", a, b);
		size[i][0] = solve(a);
		size[i][1] = solve(b);
	}
}

bool judge(int c) {
	if (c == m) return true;

	for (int i = 0; i < 2; i++) {
		if (tmp[size[c][i]] == 0) continue;
		tmp[size[c][i]]--;
		if (judge(c + 1)) return true;
		tmp[size[c][i]]++;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%d%d", &n, &m);
		init(n / 6);
		printf("%s\n", judge(0) ? "YES" : "NO");
	}
	return 0;
}
