#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;

int N, M, P[maxn];

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		int s = 0, x;
		memset(P, -1, sizeof(P));
		P[0] = 0;

		int ans = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			s = ((s + x) % M + M) % M;
			if (P[s] == -1) P[s] = i;
			ans = max(ans, i - P[s]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
