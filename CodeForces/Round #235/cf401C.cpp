#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int n, m;

inline bool judge (int k) {
	if (k == 0) return false;

	int x = m/k;
	return x == 1 || (x == 2 && m%k == 0);
}

void put(int x, int y, int k) {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < x; j++) printf("1");
		if (i < y) printf("1");
		printf("0");
	}
}

void solve (int k) {
	int x = m/k, y = m%k;
	if (k < n) {
		printf("0");
		put(x, y, k);
	} else if (k == n) {
		put(x, y, k);
	} else {
		put(x, y, k-1);
		for (int i = 0; i < x; i++) printf("1");
	}
	printf("\n");
}

int main () {
	bool flag = true;
	scanf("%d%d", &n, &m);
	for (int i = n-1; i <= n+1; i++) if (judge(i)) {
		solve (i);
		flag = false;
		break;
	}
	if (flag) printf("-1\n");
	return 0;
}
