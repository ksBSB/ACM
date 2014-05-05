#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define max(a,b) (a)>(b)?(a):(b)

const int N = 1005;

struct job {
	int b, j;
}s[N];

bool cmp(const job& a, const job& b) {
	return a.j > b.j;
}

int n;

void input() {

	for (int i = 0; i < n; i++) 
		scanf("%d%d", &s[i].b, &s[i].j);
	sort(s, s + n, cmp);
}

int  solve() {
	int ans = 0, sum = 0;

	for (int i = 0; i < n; i++) {
		ans = max(ans, sum + s[i].b + s[i].j);
		sum += s[i].b;
	}
	return ans;
}

int main () {

	int cas = 1;

	while (scanf("%d", &n) == 1 && n) {

		input();
		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}
