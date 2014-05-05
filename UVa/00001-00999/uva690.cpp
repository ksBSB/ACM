#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 5;
const int M = 100;
int n, c, ans, w[N], jump[M];

bool judge (int* s, int k) {
	for (int i = 0; i < N; i++) {
		if ((s[i]>>k)&w[i]) return false;
	}
	return true;
}

void init () {
	char str[M];

	c = 0;
	ans = n * 10;
	memset(w, 0, sizeof(w));

	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		for (int j = 0; j < n; j++)
			if (str[j] == 'X')
				w[i] |= (1<<j);
	}

	for (int i = 0; i <= n; i++) {
		if (judge (w, i)) {
			jump[c++] = i;
		}
	}

	
}

void dfs (int* s, int d, int sum) {
	if (sum + jump[0] * (10 - d) > ans) return;

	if (d == 10) {
		ans = min (ans, sum);
		return;
	}

	for (int i = 0; i < c; i++) {
		if (judge (s, jump[i])) {

			int p[N];
			for (int j = 0; j < N; j++)
				p[j] = (s[j]>>jump[i])^w[j];

			dfs (p, d + 1, sum + jump[i]);
		}
	}
}

int main () {
	while (scanf("%d", &n), n) {
		init ();
		dfs (w, 1, n);
		printf("%d\n", ans);
	}
	return 0;
}
