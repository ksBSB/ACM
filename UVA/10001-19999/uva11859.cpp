#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int div_factor (int n) {
	int ret = 0;
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			ret++;
			n /= i;
		}
	}

	if (n > 1)
		ret++;
	return ret;
}

int main () {
	int cas, N, M;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		int v = 0, x;
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++) {
			int s = 0;
			for (int j = 1; j <= M; j++) {
				scanf("%d", &x);
				s += div_factor(x);
			}
			v ^= s;
		}
		printf("Case #%d: %s\n", k, v ? "YES" : "NO");
	}
	return 0;
}
