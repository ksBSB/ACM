#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 200005;

int n, cow[N];
ll s[N];

void init () {
	memset(s, 0, sizeof(s));

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cow[i]);
		s[i] = s[i-1] + (cow[i] == 1 ? 1 : 0);
	}
}

ll solve () {
	ll ans = 0;
	for (int i = n; i; i--) if (cow[i] == 0) {
		ans += s[i];
	}
	return ans;
}

int main () {
	init();
	cout << solve () << endl;
	return 0;
}
