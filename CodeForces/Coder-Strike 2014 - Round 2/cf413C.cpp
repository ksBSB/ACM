#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 105;

struct state {
	ll val;
	int vis;
}s[N];
int n, m, k;

bool cmp (const state& a, const state& b) {
	if (a.vis != b.vis) 
		return a.vis < b.vis;
	return a.val > b.val;
}

int main () {
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; i++) {
		cin >> s[i].val;
		s[i].vis = 0;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		s[k].vis = 1;
	}

	sort(s + 1, s + n + 1, cmp);
	ll sum = 0;

	for (int i = 1; i <= n; i++) {
		if (s[i].vis) {
			sum += max(sum, s[i].val);
		} else {
			sum += s[i].val;
		}
	}
	cout << sum << endl;
	return 0;
}
