#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;

int n, m, c[N], s[N];

bool cmp(const int& a, const int& b) {
	return a > b;
}

int main () {
	int cnt = 0, p = 0, q = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &m);
		int tmp = m / 2;
		for (int j = 0; j < m; j++) {
			scanf("%d", &c[j]);
			if (j < tmp) p += c[j];
			else q += c[j];
		}

		if (m & 1) {
			q -= c[tmp];
			s[cnt++] = c[tmp];
		}
	}

	sort(s, s + cnt, cmp);
	for (int i = 0; i < cnt; i++) {
		if (i & 1) q += s[i];
		else p += s[i];
	}

	printf("%d %d\n", p, q);
	return 0;
}
