#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, A, B, L;

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int ans = 0, len = 0;
		scanf("%d%d%d%d", &N, &A, &B, &L);

		int l, r;
		while (N--) {
			scanf("%d%d", &l, &r);
			len += r - l;
			ans += max(len * A - (r - len) * B - ans, 0);
		}
		printf("Case #%d: %d\n", kcas, ans);
	}
	return 0;
}
