#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

const int N = 270000;
typedef long long ll;

int n, m;
ll v[N];

void add(int x, int val) {
	while (x <= n) {
		v[x] += val;
		x += (x & (-x));
	}
}

void init() {
	scanf("%d%d", &n, &m);
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++) add(i, 1);
}

int sum(int k) {
	int x = 0, s = 0;

	for (int i = 18; i >= 0; i--) {
		if (x + (1<<i) < n && s + v[x+ (1<<i)] < k) {
			x += (1<<i);
			s += v[x];
		}
	}
	return x+1;
}

ll solve() {
	int k;
	ll ans = 0;

	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		int s = sum(k);
		ans += s;
		add(s, -1);
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		cout << "Case " << i <<": " << solve() << endl;
	}
	return 0;
}
