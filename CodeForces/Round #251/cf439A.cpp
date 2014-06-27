#include <cstdio>
#include <cstring>

int main () {
	int n, d, t, s = 0;

	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		s += t;
	}

	s += (n - 1) * 10;

	if (s > d)
		printf("-1\n");
	else {
		int tmp = d - s;
		printf("%d\n", n * 2 - 2 + tmp / 5);
	}
	return 0;
}
