#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<ll, int> pii;
const int maxs = (1<<20) + 5;
const int maxn = 55;
const int maxm = 25;
const ll x = 123;

int N, L, T, C[maxs];
ll D[maxs];
char str[maxn][maxm];

inline int idx(char ch) {
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a';
	return ch - 'A' + 26;
}

inline int bitcount(ll x) {
	return x == 0 ? 0 : bitcount(x>>1) + (x&1);
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", str[i]);
	L = strlen(str[0]);
	T = (1<<L);

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int s = 0;
			for (int k = 0; k < L; k++)
				s |= (str[i][k] == str[j][k]) << k;
			D[s] |= (1LL<<i) | (1LL<<j);
		}
	}

	for (int i = T-1; i; i--) {
		for (int j = 0; j < L; j++)
			if (i&(1<<j))
				D[i^(1<<j)] |= D[i];
		C[i] = N - bitcount(D[i]);
	}
}

double dp[maxs], p[100];

int main () {
	init();

	if (N == 1) {
		printf("%.9lf\n", 0.0);
		return 0;
	}

	dp[0] = 1;
	for (int u = 0; u < T; u++) {
		int bit = bitcount(u), sum = N - C[u];
		double mv = dp[u] / (L - bit);
		if (N == C[u]) continue;

		for (int i = 0; i < L; i++) {
			if (u&(1<<i))
				continue;
			int s = u | (1<<i);
			double a = 1.0 * (C[s] - C[u]) / sum;

			dp[s] += mv * (1 - a);
			p[bit+1] += mv * a;
		}
	}

	/*
	double sum = 0;
	for (int u = 1; u <= L; u++) {
		printf("%lf\n", p[u]);
		sum += p[u];
	}
	printf("%lf!\n", sum);
	*/

	double ans = 0;
	for (int i = 1; i <= L; i++)
		ans += p[i] * i;
	printf("%.9lf\n", ans);
	return 0;
}
