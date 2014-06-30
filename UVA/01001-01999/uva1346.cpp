#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 70000;

struct song {
	int key;
	int l;
	double q;
	double k;
}s[N];
int n, S;

void init() {
	memset(s, 0, sizeof(s));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%lf", &s[i].key, &s[i].l, &s[i].q);
		s[i].k = s[i].l / s[i].q;
	}
	scanf("%d", &S);
}

bool cmp(const song& a, const song& b) {
	return a.k - b.k < 1e-9;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		sort(s, s + n, cmp);
		printf("%d\n", s[S - 1].key);
	}
	return 0;
}
