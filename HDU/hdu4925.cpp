#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;

int solve () {
	if (N == 1 || M == 1) {
		if (N == 1 && M == 1)
			return 1;
		int n = max(N, M);
		int s = (n + 1) / 2;
		int t = (n&1 ? 2 : 1);
		return 2 * t + 4 * (s - t);
	}

	int s = (N * M + 1) / 2;
	int t = 1 + (N&1) + (M&1) + ((N&1)==(M&1));
	int k = N + M - 2 - t;
	return 4 * t + 8 * k + 16 * (s - k - t);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		printf("%d\n", solve());
	}
	return 0;
}
