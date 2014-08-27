#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int N, K;

bool check (int s, int f, int n) {

	if (f == 0)
		return false;

	int p = 1;
	for (int i = 1; i < n; i++) {
		if (p == f)
			p++;

		if (s <= p)
			return false;
		s -= p;
		p++;
	}

	while (true) {
		if (s < p)
			return false;
		if (s != f)
			return true;
		p++;
		s--;
	}
	return false;
}

bool judge () {
	int n = (int)sqrt((double)N);

	while (n) {
		if (check(n * n, N - n * n, K - 1))
			return true;
		n--;
	}
	return false;
}

int main () {
	while (scanf("%d%d", &N, &K) == 2) {
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
