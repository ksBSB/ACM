#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 2000000;

int N, fenw[maxn+5], vis[maxn+5], num[maxn+5];

void add (int x, int v) {
	while (x <= maxn) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

int find (int k) {
	int c = 0, p = 0;
	for (int i = 20; i >= 0; i--) {
		p += (1<<i);
		if (p > maxn || c + fenw[p] >= k)
			p -= (1<<i);
		else
			c += fenw[p];
	}
	return p + 1;
}

int init (int n) {
	memset(fenw, 0, sizeof(fenw));

	for (int i = 1; i <= maxn; i += 2)
		add(i, 1);
	n /= 2;

	for (int i = 2; i <= n; i++) {
		int l = find(i);

		if (n < l)
			break;

		for (int j = l; j <= n; j += l)
			vis[j] = find(j);
		for (int j = l; j <= n; j += l)
			add(vis[j], -1);
		n -= n / l;
	}

	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		num[i] = find(i);
		vis[num[i]] = 1;
	}
	return n;
}

void solve (int n) {
	//int k = upper_bound(num.begin(), num.end(), n / 2) - num.begin();
	//int k = lower_bound(num.begin(), num.end(), n / 2) - num.begin();
	if ((n&1) == 0) {
		int k = upper_bound(num + 1, num + 1 + N, n / 2) - num - 1;
		while (k >= 1) {
			if (vis[n - num[k]]) {
				printf("%d is the sum of %d and %d.\n", n, num[k], n - num[k]);
				return;
			}
			k--;
		}
	}
	printf("%d is not the sum of two luckies!\n", n);
}

int main () {
	N = init(maxn);

	int n;
	while (~scanf("%d", &n)) {
		solve(n);
	}
	return 0;
}
