#include <stdio.h>
#include <string.h>

const int N = 1005;

int n, m, c, v[N];
char str[N];

int main () {

	bool flag = true;
	c = 0;
	memset(v, 0, sizeof(v));

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		int p = -1, q = -1;

		for (int j = 0; j < m; j++) {
			if (str[j] == 'G') q = j;
			if (str[j] == 'S') p = j;
			if (p >= 0 && q >= 0) break;
		}

		int k = p - q;
		if (k < 0) flag = false;
		else {
			if (v[k] == 0) c++;
			v[k]++;
		}
	}
	printf("%d\n", flag ? c : -1);
	return 0;
}
