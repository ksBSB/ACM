#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;
int n, a[N];

void init() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, a + n);
}

int solve() {
	if (n == 1) return a[0];
	else if (n == 2) return a[1];

	int ans = 0, e = n % 2 + 1;
	for (int i = n - 1; i > e; i -= 2) {
		ans += a[0] + a[i];
		if (a[1] * 2 < a[i-1] + a[0]) {
			ans += a[1] * 2;
		} else {
			ans += a[i-1] + a[0];
		}
	}
	if (n % 2) ans += a[0] + a[1] + a[2];
	else ans += a[1];
	return ans;
}

void put() {
	if (n == 1) printf("%d\n", a[0]);
	else if (n == 2) printf("%d %d\n", a[0], a[1]);
	else if (n == 3) {
		printf("%d %d\n%d\n", a[0], a[1], a[0]);
		printf("%d %d\n", a[0], a[2]);
	} else {
		int e = n % 2 + 1;
		for (int i = n - 1; i > e; i -= 2) {
			if (a[1] * 2 < a[i-1] + a[0]) {
				printf("%d %d\n%d\n", a[0], a[1], a[0]);
				printf("%d %d\n%d\n", a[i-1], a[i], a[1]);
			} else {
				printf("%d %d\n%d\n", a[0], a[i-1], a[0]);
				printf("%d %d\n%d\n", a[0], a[i], a[0]);
			}
		}
		if (n % 2) {
			printf("%d %d\n%d\n", a[0], a[1], a[0]);
			printf("%d %d\n", a[0], a[2]);

		} else printf("%d %d\n", a[0], a[1]);
	}
}

int main() {
	int cas; scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
		put();
		if(cas) printf("\n");
	}
	return 0;
}
