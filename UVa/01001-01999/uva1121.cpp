#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 100005;
int n, k, num[N];

void init() {
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
}

int solve() {
	int ans = n + 1, sum = 0;
	int l = 0, r = 0;
	while (r < n) {
		sum += num[r++];
		while (sum >= k) {
			ans = min(ans, r - l);
			sum -= num[l++];
		}
	}
	return ans == n + 1 ? 0 : ans;
}

int main() {
	while (scanf("%d%d", &n, &k) == 2) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
