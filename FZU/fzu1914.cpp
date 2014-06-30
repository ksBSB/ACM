#include <stdio.h>
#include <string.h>

#define ll long long

const int N = 500005;

int n, v[N];
int a[N];

void init() {
	scanf("%d", &n);
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
}

int solve() {

	int ans = n;
	ll sum = 0;

	for (int i = n - 1; i >= 0 && ans; i--) {

		if (sum <= 0) {
			sum += a[i];
			if (sum <= 0) {
				ans--;
				v[i] = 1;
			}
		} else if (a[i] <= 0) {
			sum = a[i];
			ans--;
			v[i] = 1;
		}
	}

	int i = n - 1;
	
	while (sum <= 0) {

		sum += a[i];

		if (sum <= 0 && !v[i]) {
			v[i] = 1;
			ans--;
		}
		i--;
		if (ans == 0 || i < 0) break;
	}

	return ans;
}

int main () {

	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %d\n", i, solve());
	}
	return 0;
}
