#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 100005;

int n, x[N], y[N], z[N];

void init() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
}

inline int sign(int k) {
	return k ? -1 : 1;
}

int solve() {
	int ans = 0;
	for (int i = 0; i < 8; i++) {
		int Max = -INF, Min = INF;
		for (int j = 0; j < n; j++) {
			int k = x[j] * sign(i&4) + y[j] * sign(i&2) + z[j] * sign(i&1);	
			Max = max(k, Max);
			Min = min(k, Min);
		}	
		ans = max(ans, Max - Min);
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case #%d: %d\n", i, solve());
	}
	return 0;
}
