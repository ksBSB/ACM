#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;
const int maxn = 40005;
const int x = 123;

int N, M, pos, Rank[maxn];
char str[maxn];
ll h[maxn], xp[maxn], Hash[maxn];

void init () {
	scanf("%s", str);
	N = strlen(str);

	h[N] = 0;
	for (int i = N - 1; i >= 0; i--)
		h[i] = h[i+1] * x + str[i] - 'a';
	xp[0] = 1;
	for (int i = 1; i <= N; i++)
		xp[i] = xp[i-1] * x;
}

bool cmp (const int& a, const int& b) {
	return Hash[a] < Hash[b] || (Hash[a] == Hash[b] && a < b);
}

bool judge (int l) {
	int c = 0, n = N - l + 1;
	pos = -1;

	for (int i = 0; i < n; i++) {
		Rank[i] = i;
		Hash[i] = h[i] - h[i+l] * xp[l];
	}

	sort (Rank, Rank + n, cmp);
	for (int i = 0; i < n; i++) {
		if (i == 0 || Hash[Rank[i]] != Hash[Rank[i-1]]) c = 0;
		if (++c >= M)
			pos = max(pos, Rank[i]);
	}
	return pos >= 0;
}

void bsearch () {
	if (!judge(1)) {
		printf("none\n");
		return;
	}

	int l = 1, r = N + 1;
	while (r - l > 1) {
		int mid = (r + l) / 2;
		if (judge(mid))
			l = mid;
		else
			r = mid;
	}
	judge(l);
	printf("%d %d\n", l, pos);
}

int main () {
	while (scanf("%d", &M) == 1 && M) {
		init();
		bsearch();
	}
	return 0;
}
