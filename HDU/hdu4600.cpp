#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1005;

int W, H, N, D, M, S[20];
ll V[maxn], A[maxn];

void init () {
	memset(S, 0, sizeof(S));
	scanf("%d%d%d%d%d", &W, &H, &N, &D, &M);
	int w = W % 3, h = H % 3;
	S[9] = (W/3) * (H/3);
	S[w*3] += (H/3);
	S[h*3] += (W/3);

	if (w * h == 1) {
		S[5]++; S[3] -= 2; S[1] += 2;
	} else if (w * h == 4) {
		S[8]++; S[6] -= 2; S[4] += 2;
	} else if (w * h == 2) {
		S[7]++; S[6]--; S[3]--; S[2] += 2;
	}
}

ll solve (int in, int ot, int n) {
	int d = D / n, c[20];
	memset(V, 0, sizeof(V));
	V[0] = M;

	for (int i = 0; i < d; i++) {
		int k = V[i] / in, area = 0, p = 9;
		memset(c, 0, sizeof(c));

		while (p * ot > in) {
			int t = min(S[p] - c[p], k);
			k -= t, c[p] += t;
			area += t * p;
			V[i] -= t * in;

			if (k == 0) break;
			p--;
		}
		V[i+1] = V[i] + area * ot;
	}
	return V[d];
}

ll solve (int in, int ot, int n, int m) {
	int d = D, c[10], p = 9;
	memset(c, 0, sizeof(c));
	memset(V, 0, sizeof(V));
	memset(A, 0, sizeof(A));
	V[0] = M;

	for (int i = 0; i < d; i++) {
		int k = V[i] / in, nw = 0;

		while (i + n <= d) {
			int ti = (d - i - n) / m + 1;
			if (1LL * p * ot * ti <= in) break;

			int t = min(S[p] - c[p], k);
			k -= t, c[p] += t;
			nw += 1LL * t * p;
			V[i] -= 1LL * t * in;

			if (k == 0) break;
			p--;
		}

		if (i + m <= d) {
			V[i+m] += A[i] * ot;
			A[i+m] += A[i];
		}

		if (nw) {
			V[i+n] += nw * ot;
			A[i+n] += nw;
		}

		V[i+1] += V[i];
	}

	return V[d];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		ll ans = M;
		int q, p, n, m;
		for (int i = 0; i < N; i++) {
			scanf("%d%d%d%d", &q, &p, &n, &m);
			if (m == 0)
				ans = max(ans, solve(q, p, n));
			else
				ans = max(ans, solve(q, p, n, m));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
