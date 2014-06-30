#include <stdio.h>

const int N =  105;
int n, c[N];

void scanfINT(int& num) {
	bool flag = false;
	char ch;
	num = 0;
	while (ch = getchar(), ch < '0' || ch > '9') {
		if (ch == '-') { flag = true; break; }
	}

	num = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9') {
		num = num * 10 + ch - '0';
	}
	if (flag) num *= -1;
}

void init() {
	int a;
	for (int i = 0; i < n; i++) {
		scanfINT(a);
		c[a]++;
	}
}

void solve() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		while (c[i]) {
			printf("%d", i);
			c[i]--;
			cnt++;
			if (cnt == n) printf("\n");
			else printf(" ");
		}
	}
}

int main() {
	while (scanfINT(n), n) {
		init();
		solve();
	}
	return 0;
}
