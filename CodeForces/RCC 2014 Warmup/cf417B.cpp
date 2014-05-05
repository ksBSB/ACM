#include <cstdio>
#include <cstring>

const int N = 1e5+5;

int main () {
	int n, x, k, c[N];
	bool flag = true;

	memset(c, 0, sizeof(c));

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &x, &k);

		if (x < c[k]) 
			continue;
		else if (x == c[k])
			c[k]++;
		else
			flag = false;
	}

	printf("%s\n", flag ? "YES" : "NO");
	return 0;
}
