#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 50;
int n, m, d[N], h[N];

void init() {
	int a;
	memset(d, 0, sizeof(d));
	memset(h, 0, sizeof(h));

	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		d[a]++;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d", &a);
		h[a]++;
	}
}

int solve() {
	int ans = 0;
	for (int i = 1; i <= 20; i++) {
		ans += max(d[i], h[i]) * i;
	}
	return ans;
}

int main () {
	while (scanf("%d%d", &n, &m) == 2 && n && m) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
