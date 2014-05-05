#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int N = 10005;
const int INF = 0x3f3f3f3f;

int n, m, flag, d[N];
int x[N], y[N], v[N];

void init() {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &x[i], &y[i], &v[i]);
}

void BF() {
	flag = 0;
	for (int i = 0; i < n; i++) d[i] = INF;
	d[0] = 0;

	for (int k = 1; k < n; k++) {
		for (int i = 0; i < m; i++) {
			int a = x[i], b = y[i];
			if (d[a] < INF)
				d[b] = min(d[a] + v[i], d[b]);
		}
	}

	for (int i = 0; i < m; i++) {
		int a = x[i], b = y[i];
		if (d[b] > d[a] + v[i]) {
			flag = 1;
			return;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		BF();
		printf("%s\n", flag ? "possible" : "not possible");
	}
	return 0;
}
