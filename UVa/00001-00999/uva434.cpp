#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 10;

int n, f[N], r[N];

void init() {
	memset(f, 0, sizeof(f));
	memset(r, 0, sizeof(r));

	scanf("%d", &n);
	int a;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a); f[a]++;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &a); r[a]++;
	}
}

void solve() {
	int Min = 0, Max = 0, left = n, right = n;

	for (int i = 0; i < N; i++) {
		Min += max(f[i], r[i]) * i;
		Max += left * right;
		left -= f[i];
		right -= r[i];
	}
	printf("Matty needs at least %d blocks, and can add at most %d extra blocks.\n", Min, Max - Min - n * n);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
