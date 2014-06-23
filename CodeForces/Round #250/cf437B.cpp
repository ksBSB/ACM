#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5+5;

struct state {
	int num;
	int low;
}s[N];

int n, sum, cnt, ans[N];

inline bool cmp (const state&a, const state& b) {
	return a.low > b.low;
}

int getLow (int x) {
	int c = 0;
	while (x) {
		if (x&1)
			return 1<<c;
		x /= 2;
		c++;
	}
	return 0;
}

void init () {

	scanf("%d%d", &sum, &n);
	for (int i = 1; i <= n; i++) {
		s[i].num = i;
		s[i].low = getLow(i);
	}

	cnt = 0;
	sort(s + 1, s + n + 1, cmp);
}

int main () {
	init ();
	for (int i = 1; i <= n; i++) {
		if (s[i].low <= sum) {
			ans[cnt++] = s[i].num;
			sum -= s[i].low;
		}
	}

	if (sum)
		printf("-1\n");
	else {
		printf("%d\n%d", cnt, ans[0]);
		for (int i = 1; i < cnt; i++)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}
