#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
const int N = 100005;
typedef long long ll;

struct order {
	int s;
	ll x, y;
}o[N];
int n, m, num[N], ans[N], c, cnt;
ll k[N];

void handle () {
	c = 0;
	for (int i = 0; i < m; i++) {
		if (o[i].s == 1) {
			num[c++] = o[i].x;
			if (c >= 100000) return;
		} else {
			for (ll t = 0; t < o[i].y; t++) {
				for (ll j = 0; j < o[i].x; j++) {
					num[c++] = num[j];
					if (c >= 100000) return;
				}
			}
		}
	}
}

void init () {
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &o[i].s);
		if (o[i].s == 1) cin >> o[i].x;
		else cin >> o[i].x >> o[i].y;
	}

	handle();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) cin >> k[i];
}

void solve () {


	int i = 0, j = 0;
	ll p = 0;
	while (i < n) {
		while (j < m) {
			if (o[j].s == 1) {
				p++;  j++;
				if (p == k[i]) {
					ans[i] = o[j-1].x; i++;
					if (i >= n) return;
					break;
				}
			} else {
				ll q = p;
				p += o[j].x * o[j].y;
				if (p >= k[i]) {
					while (i < n) {
						if (k[i] <= p) {
							ans[i] = num[(k[i] - q - 1) % o[j].x % 100000];
							i++;
							if (i >= n) return ;
						} else {
							j++; break;
						}
					}
				} else j++;
			}
		}
	}
}

int main () {
	init ();
	solve ();
	printf("%d", ans[0]);
	for (int i = 1; i < n; i++) printf(" %d", ans[i]);
	printf("\n");
	return 0;
}
