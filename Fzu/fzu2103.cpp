#include <stdio.h>
#include <string.h>
#include <math.h>

typedef long long ll;

const int N = 60;

int n, k, r, tmp, v[N];
double P, p[N], pi, C[N][N];

void init() {
	memset(C, 0, sizeof(C));
	for (int i = 0; i <= 52; i++) {
		C[0][i] = 1;
		for (int j = 1; j <= i; j++)
			C[j][i] = C[j - 1][i] * (i - j + 1) / j;
	}
}

void input() {
	P = 1; pi = 0;
	scanf("%d%d%d", &n, &k, &r);
	memset(v, 0, sizeof(v));
	memset(p, 0, sizeof(p));

	int a;
	for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
	for (int i = 1; i <= r; i++) {
		scanf("%d", &a); v[a]++;
	}

	for (int i = 1; i <= n; i++) if (v[i]) {
		tmp = i; break;
	}

	int t = k;
	for (int i = tmp + 1; i <= n; i++) if (v[i]) {
		P *= pow(p[i], v[i]) * C[v[i]][t];
		t -= v[i];
	}
	for (int i = 1; i < tmp; i++) pi += p[i];
}

double solve() {
	int top = k - r + v[tmp];
	double ans = 0;

	for (int i = v[tmp]; i <= top; i++)
		ans += pow(p[tmp], i) * C[i][top] * pow(pi, top - i);

	return P * ans;
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		input();
		printf("%.6lf\n", solve());
	}
	return 0;
}
