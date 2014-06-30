#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 5005;

int n, e[N], w[N], l, r;

void init() {
	scanf("%d", &n);
	int W = 0, E = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &e[i], &w[i]);
		E += e[i]; W += w[i];
	}
	l = 0; r = max(E, W);
}

bool judge(int c) {
	int cnt = 0, W = 0, E = 0, nw, ne;
	for (int i = 0; i < n; i++) {
		W += w[i]; E += e[i];
		nw = max(W - c, 0);
		ne = max(E - c, 0);
		if (nw + ne > cnt) return false;
		W -= nw; E -= ne;
		cnt -= nw + ne;

		if (W == 0 && E > 0) {
			E--;
		} else if (E == 0 && W > 0) {
			W--;
		} else if (W > 0 && E > 0 && W + E > cnt) {
			cnt++;
		}
	}
	return true;
}

int solve() {
	while (l < r) {
		int mid = (l + r) / 2;
		if (judge(mid)) r = mid;
		else l = mid + 1;
	}
	return max(r - 1, 0);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
