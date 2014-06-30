#include <stdio.h>
#include <string.h>

const int N = 10005;

int n, c, v[N], p[N], rec;

void init() {
	c = 0;
	memset(p, -1, sizeof(p));
	memset(v, 0, sizeof(v));

	int k, a, m;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d", &m);
		for (int j = 0; j < m; j++) {
			scanf("%d", &a); p[a] = ++c;
		}
	}
}

void dfs(int d, int aid) {

	if (v[aid]) { 
		for (int i = 1; i <= n; i++) if (p[i] == -1) {
			printf("%d %d\n", d, i);
			p[i] = p[d]; rec = i; p[d] = -1;
			return ;
		}
	}

	v[d] = 1;

	if (p[aid] != -1) dfs(aid, p[aid]);
	p[aid] = p[d]; p[d] = -1;
	printf("%d %d\n", d, aid);
	v[d] = 0;
}

void solve() {
	bool flag = false;

	for (int i = 1; i <= n; i++) if (p[i] != i && p[i] != -1) {
		rec = -1; flag = true;
	   	dfs(i, p[i]); 

		if (rec != -1) {
			printf("%d %d\n", rec, p[rec]);
			p[i] = p[rec]; p[rec] = -1;
		}
	}

	if (flag == false) printf("No optimization needed\n");
}

int main () {
	int cas; scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if(cas) printf("\n");
	}
	return 0;
}
