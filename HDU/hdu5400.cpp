#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;
int N, D1, D2, A[maxn];

int main () {
	while (scanf("%d%d%d", &N, &D1, &D2) == 3) {
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		ll ans = N;
		int l = 1, r = 1;
		while (l <= N) {
			while (r < N && A[r] + D1 == A[r+1]) r++;
			while (r < N && A[r] + D2 == A[r+1]) r++;
			if (r == l) {
				r++, l++;
				continue;
			}
			int n = r - l;
			ans = ans + 1LL * n * (n+1) / 2;
			l = r;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
