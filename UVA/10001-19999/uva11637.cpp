#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e5;

int N, K;
long double frc[maxn+5];

double solve () {
	if (N == 1)
		return 0;

	if (N - 2 * K - 1 <= 0)
		return N;

	double ret = 0;
	for (int i = 1; i <= N; i++) {
		int x = min(K, i - 1)  + min(K, N - i);
		if (N >= x + 2 * K + 1)
			ret += exp(frc[N-1-2*K] + frc[N-1-x] - frc[N-1] - frc[N - 1 - x - 2 * K]);
	}
	return N - ret;
}

int main () {
	int cas = 1;
	frc[0] = 0;
	for (int i = 1; i <= maxn; i++)
		frc[i] = frc[i-1] + log((long double)i);

	while (scanf("%d%d", &N, &K) == 2 && N + K) {
		printf("Case %d: %.4lf\n", cas++, solve());
	}
	return 0;
}
