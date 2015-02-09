#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;
const int maxm = 1e5 + 5;
typedef long long ll;

int N, M, DX, DY, C[maxn], X[maxm], Y[maxm], V[maxm];

inline void exgcd (int a, int b, int& d, int& x, int& y) {
	if (!b) {
		d = a; x = 1; y = 0;
	} else {
		exgcd(b, a%b, d, y, x);
		y -= x * (a / b);
	}
}

int main () {
	scanf("%d%d%d%d", &N, &M, &DX, &DY);

	int x, y, t;
	exgcd(N, -DX, t, x, y);
	ll T = (y * t % N + N) % N;

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &X[i], &Y[i]);
		V[i] = (Y[i] + T * X[i] % N * DY % N + N) % N;
		C[V[i]]++;
	}

	int ans = 0;
	for (int i = 0; i < N; i++)
		if (C[i] > ans) {
			ans = C[i];
			y = i;
		}

	for (int i = 0; i < M; i++)
		if (V[i] == y) {
			printf("%d %d\n", X[i], Y[i]);
			break;
		}

	return 0;
}
