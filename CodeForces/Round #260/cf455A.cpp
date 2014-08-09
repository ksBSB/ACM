#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5+5;

int n, arr, c[maxn];

int main () {
	cin >> n;
	memset(c, 0, sizeof(c));

	for (int i = 0; i < n; i++) {
		cin >> arr;
		c[arr]++;
	}

	ll p = 0, q = 0;

	for (int i = 1; i < maxn; i++) {

		ll tmp = q + 1LL * i * c[i];
		q = max(p, q);
		p = tmp;
	}

	cout << max(p, q) << endl;
	return 0;
}
