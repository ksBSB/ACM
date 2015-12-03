#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int mod = 10007;

int N, A[maxn];

int main () {
	while (scanf("%d", &N) == 1) {
		int sum = 0, ans = 0, mv = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &A[i]);
			sum += A[i];
			int k = (A[i] * 1890 + 143) % mod;
			A[i] = k - A[i];
		}

		for (int i = 1; i <= N; i++) {
			mv += A[i];
			ans = max(ans, mv);
			if (mv < 0) mv = 0;
		}
		printf("%d\n", ans + sum);
	}
	return 0;
}
