#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 1;
#define lowbit(x) ((x)&(-x))

int N, fenw[maxn + 5], ans[maxn + 5];
struct Seg {
	int l, r, id;
	friend bool operator < (const Seg& a, const Seg& b) {
		if (a.l != b.l)
			return a.l < b.l;
		return a.r > b.r;
	}
}s[maxn + 5];

void add (int x, int w) {
	while (x <= maxn) {
		fenw[x] += w;
		x += lowbit(x);
	}
}

int sum (int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		memset(fenw, 0, sizeof(fenw));
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", &s[i].l, &s[i].r);
			s[i].l++, s[i].r++, s[i].id = i;
		}

		sort(s + 1, s + N + 1);

		for (int i = 1; i <= N; i++) {
			if (i != 1 && s[i].l == s[i-1].l && s[i].r == s[i-1].r)
				ans[s[i].id] = ans[s[i-1].id];
			else 
				ans[s[i].id] = sum(maxn) - sum(s[i].r - 1);
			add(s[i].r, 1);
		}

		for (int i = 1; i <= N; i++)
			printf("%d%c", ans[i], i == N ? '\n' : ' ');
	}
	return 0;
}
