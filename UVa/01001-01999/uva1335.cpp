#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 100005;

int n, r[N], right[N], left[N];

void init() {
	memset(r, 0, sizeof(r));

	for (int i = 1; i <= n; i++)	scanf("%d", &r[i]);
	r[n + 1] = r[1];
}

bool test(int tmp) {
	int x = r[1], y = tmp - r[1];
	left[1] = x, right[1] = 0;

	for (int i = 2; i <= n; i++) {
		if (i % 2) {
			right[i] = min(y - right[i - 1], r[i]);
			left[i] = r[i] - right[i];
		} else {
			left[i] = min(x - left[i - 1], r[i]);
			right[i] = r[i] - left[i];
		}
	}
	return left[n] == 0;
}

int solve() {
	if (n == 1) return r[1];
	
	int L = 0, R = 0;

	for (int i = 1; i <= n; i++) L = max(L, r[i] + r[i + 1]);

	if (n % 2) {
		for (int i = 1; i <= n; i++) R = max(R, r[i] * 3);

		while (L < R) {
			int M = (L + R) / 2;
			if (test(M)) R = M;
			else L = M + 1;
		}
	}

	return L;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
