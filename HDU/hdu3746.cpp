#include <stdio.h>
#include <string.h>

const int N = 1e5+5;

int n, next[N];
char str[N];

void getNext () {
	n = strlen (str+1);
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p > 0 && str[p+1] != str[i])
			p = next[p];

		if (str[p+1] == str[i])
			p++;
		next[i] = p;
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str+1);
		getNext();

		if (next[n] == 0) printf("%d\n", n);
		else {
			int k = n - next[n];
			if (n%k == 0) printf("0\n");
			else printf("%d\n", k - (n - (n/k) * k));
		}
	}
	return 0;
}
