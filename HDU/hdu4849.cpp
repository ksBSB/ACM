#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxd = 1005;
const int maxn = maxd * maxd;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, M;
ll X[maxn], Y[maxn], Z[maxn];
ll C[maxd][maxd], d[maxd];

void init_distant () {
	for (int i = 1; i < N * N; i++) {
		if (i >= 2) {
			X[i] = (12345 + X[i-1] * 23456 + X[i-2] * 34567 + (X[i-1] * X[i-2] % 5837501) * 45678)  % 5837501;
			Y[i] = (56789 + Y[i-1] * 67890 + Y[i-2] * 78901 + (Y[i-1] * Y[i-2] % 9860381) * 89012)  % 9860381;
		}
		Z[i] = (X[i] * 90123 + Y[i]) % 8475871 + 1;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)
				C[i][j] = 0;
			else
				C[i][j] = Z[i*N+j];
		}
	}
}

ll dijstra () {
	int v[maxd];
	memset(v, 0, sizeof(v));
	for (int i = 0; i < N; i++)
		d[i] = INF;
	d[0] = 0;

	ll ans = INF;
	for (int i = 0; i < N; i++) {

		int u = 0;
		ll dis = INF;
		for (int j = 0; j < N; j++) {
			if (d[j] < dis && v[j] == 0) {
				u = j;
				dis = d[j];
			}
		}

		v[u] = 1;
		if (d[u] % M < ans && u)
			ans = d[u] % M;

		for (int j = 0; j < N; j++) {
			if (d[u] + C[u][j] < d[j])
				d[j] = d[u] + C[u][j];
		}
	}
	return ans;
}

int main () {
	while (scanf("%d%d%lld%lld%lld%lld", &N, &M, &X[0], &X[1], &Y[0], &Y[1]) == 6) {
		init_distant();
		printf("%lld\n", dijstra());
	}
	/*
	while (cin >> N >> M >> X[0] >> X[1] >> Y[0] >> Y[1]) {
		init_distant();
		cout << dijstra() << endl;
	}
	*/
	return 0;
}
