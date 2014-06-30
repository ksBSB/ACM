#include <stdio.h>
#include <string.h>
const int N = 105;
const int M = 4505;
const int MAX = 10000005;

int n, v, dp[MAX], vis[M], top, sum;
int l[N], r[N];

void read() {
	top = 1 << 30;
	scanf("%d%d", &v, &n);
	v *= 1000;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &l[i], &r[i]);
		if (l[i] * r[i] / (r[i] - l[i]) < top)
			top = l[i] * r[i] / (r[i] - l[i]);
	}
}

void handle() {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++) {
		for (int j = l[i]; j <= r[i] && j <= v; j++)
			vis[j] = 1;
	}
}

int solve() {
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 0; i <= 4500; i++) {
		if (vis[i]) {
			for (int j = i; j <= v; j++) {
				if (dp[j - i])
					dp[j] = 1;
			}
		}
	}

	for (int i = v; i >= 0; i--)
		if (dp[i]) return i;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		read();
		if (v >= top) printf("0\n");
		else {
			handle();
			if (v < M && vis[v]) printf("0\n");
			else printf("%d\n", v - solve());
		}
		if (cas) printf("\n");
	}
	return 0;
}
