#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 105;
int n, d, r, after[N], even[N];

void init() {
	for (int i = 0; i < n; i++) scanf("%d", &after[i]);
	for (int i = 0; i < n; i++) scanf("%d", &even[i]);
	sort(after, after + n);
	sort(even, even + n);
}

int solve() {
	int ans = 0, p = 0;
	for (int i = n - 1; i >= 0; i--) {
		int c = after[i] + even[p++];
		if (c > d) ans += c - d;
	}
	return ans;
}

int main () {
	while (scanf("%d%d%d", &n, &d, &r) == 3 && n && d && r) {
		init();
		printf("%d\n", solve() * r);
	}
	return 0;
}
