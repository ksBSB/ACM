#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 505;

int solve (int n, int m) {
	return n / m + (n % m ? 1 : 0);
}

int N, C[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int a, b, m = 0;
		scanf("%d", &N);
		memset(C, 0, sizeof(C));
		for (int i = 0; i < N; i++) {
			scanf("%d%d", &a, &b);
			C[a] += b;
		}
		for (int i = 0; i <= 500; i++)
			m += solve(C[i], 64);

		printf("%d\n", solve(m, 36));
	}
	return 0;
}
