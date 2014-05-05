#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

bool judge (int s) {
	int k = sqrt(s);
	return k * k == s;
}

int main () {
	int n, m;
	int a, b, c, d;

	scanf("%d%d", &n, &m);

	while (true) {
		a = rand()%100 + 1;
		b = rand()%100 + 1;
		c = rand()%100 + 1;
		d = rand()%100 + 1;

		if (judge(a * a * (m-1) + b * b)
		 && judge(a * a * (n-1) + c * c)
		 && judge(b * b * (n-1) + d * d)
		 && judge(c * c * (m-1) + d * d) )
			break;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++)
			printf("%d ", a);
		printf("%d\n", b);
	}

	for (int i = 1; i < m; i++)
			printf("%d ", c);
	printf("%d\n", d);
	return 0;
}
