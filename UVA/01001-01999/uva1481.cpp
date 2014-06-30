#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 3005;

int n, v[N], a[N];

void init() {
	int k;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) {
		scanf("%d", &k);
		v[k] = i;
	}
}

int solve() {
	int l, r, k, ans = 0;
	for (int i = 0; i < n; i++) {
		l = r = v[a[i]]; k = 1;
		for (int j = i + 1; j < n; j++) {
			l = min(l, v[a[j]]);
			r = max(r, v[a[j]]);
			k++;
			if (r - l + 1 == k) ans++;
		}
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
