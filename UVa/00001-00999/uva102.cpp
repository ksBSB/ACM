#include <stdio.h>
#include <string.h>

const int N = 5;
const char sign[5] = "BGC";

int ans, sum, v[N], t[N], c[N][N], p[N];

bool judge() {
	char s1[N], s2[N];

	for (int i = 0; i < 3; i++) {
		s1[i] = sign[t[i]];
		s2[i] = sign[p[i]];
	}
	s1[3] = s2[3] = '\0';
	return strcmp(s1, s2) < 0;
}

void dfs(int d, int s) {
	if (d == 3) {
		if (s > ans || (s == ans && judge())) {
			ans = s;
			memcpy(p, t, sizeof(t));
		}
		return ;
	}

	for (t[d] = 0; t[d] < 3; t[d]++) {
		int& u = t[d];
		if (v[u]) continue;
		v[u] = 1;
		dfs(d+1, s+c[d][u]);
		v[u] = 0;
	}
}

bool init() {
	
	sum = ans = 0;
	memset(v, 0, sizeof(v));
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (scanf("%d", &c[i][j]) != 1) return false;
			sum += c[i][j];
		}
	}

	return true;
}

int main () {

	while (init() ) {
	
		dfs(0, 0);
		for (int i = 0; i < 3; i++) printf("%c", sign[p[i]]);
		printf(" %d\n", sum - ans);
	
	}
	return 0;
}
