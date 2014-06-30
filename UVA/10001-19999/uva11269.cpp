#include <stdio.h>
#include <algorithm>

using namespace std;

const int N = 105;

struct state {
	int s, g;
}sta[N];
int n;

bool cmp(const state& a, const state& b) {
	return a.s + max(a.g, b.s) + b.g < b.s + max(b.g, a.s) + a.g;
}

void init() {
	for (int i = 0; i < n; i++) scanf("%d", &sta[i].s);
	for (int i = 0; i < n; i++) scanf("%d", &sta[i].g);
	sort(sta, sta + n, cmp);
}

int solve() {
	int S = 0, G = 0;
	for (int i = 0; i < n; i++) {
		S += sta[i].s;
		if (S > G) G = S + sta[i].g;
		else G += sta[i].g;
	}
	return G;
}

int main() {
	while (scanf("%d", &n) == 1) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
