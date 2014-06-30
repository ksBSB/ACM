#include <stdio.h>
#include <string.h>

const int N = 1000005;
const int M = 10005;

int n, m, i, next[M];
char W[M], T[N];

void getNext () {
	m = strlen(W + 1);

	int p = 0;
	for (i = 2; i <= m; i++) {
		while (p > 0 && W[p+1] != W[i])
			p = next[p];

		if (W[p+1] == W[i])
			p++;

		next[i] = p;
	}
}

int KMP () {
	int ans = 0, p = 0;
	n = strlen(T+1);

	for (int i = 1; i <= n; i++) {
		while (p > 0 && W[p+1] != T[i])
			p = next[p];

		if (W[p+1] == T[i])
			p++;

		if (p == m) {
			ans++;
			p = next[p];
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s%s", W+1, T+1);
		getNext();
		printf("%d\n", KMP());
	}
	return 0;
}
