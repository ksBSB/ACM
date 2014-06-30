#include <stdio.h>
#include <string.h>
#include <math.h>
#include <set>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int N = 105;
int g, v[N], a[N];

void init () {
	g = 0;
	memset(v, 0, sizeof(v));

	for (int i = 2; i <= 64; i++) {
		if (v[i]) {
			a[g++] = i;
			continue;
		}

		for (int j = i * 2; j <= 64; j += i) v[j] = 1;
	}
}

void solve () {
	set<ll> ans;
	ans.insert(1);

	ll MaxT = 1<<16;
	for (ll i = 2; i < MaxT; i++) {
		int ti = ceil(64 * log(2) / log(i)) - 1;
		ll now = i * i * i * i;
		ans.insert(now);
		for (int j = 1; a[j] <= ti; j++) {
			now *= (a[j] - a[j-1] == 1 ? i : i * i);
			ans.insert (now);
		}
	}

	for (set<ll>::iterator i = ans.begin(); i != ans.end(); i++)
		printf("%llu\n", *i);
}

int main () {
	init();
	solve ();
	return 0;
}
