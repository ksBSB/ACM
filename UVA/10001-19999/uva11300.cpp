#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
#define ll long long

const int N = 1000005;

ll n, aver, a[N], c[N];

void input() {
	ll sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		sum += a[i];
	}

	aver = sum / n;
	c[0] = 0;
	for (int i = 1; i < n; i++)
		c[i] = c[i - 1] - a[i] + aver;
	sort(c, c + n);
}

ll solve() {
	ll tmp = c[n / 2], ans = 0;

	for (int i = 0; i < n; i++)
		ans += abs(c[i] - tmp);
	return ans;
}

int main () {

	while (scanf("%lld", &n) == 1) {
		input();
		printf("%lld\n", solve());
	} 
	return 0;
}
