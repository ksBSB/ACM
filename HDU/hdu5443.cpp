#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, Q, A[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);

		int l, r;
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d%d", &l, &r);
			int ans = 0;
			for (int i = l; i <= r; i++) ans = max(ans, A[i]);
			printf("%d\n", ans);
		}
	}
	return 0;
}
