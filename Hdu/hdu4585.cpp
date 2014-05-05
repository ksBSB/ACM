#include <stdio.h>
#include <string.h>
#include <set>
#include <algorithm>
#include <stdlib.h>

using namespace std;
const int N = 1e5+5;
const int M = 5000005;

struct HS {
	int id, power;
}s[N];

int n, v[M];
set<int> vis;

void init () {

	vis.clear ();
	memset(v, 0, sizeof(v));

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &s[i].id, &s[i].power);
		v[s[i].power] = s[i].id;
	}

	vis.insert(s[0].power);
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init ();

		printf("%d 1\n", s[0].id);

		for (int i = 1; i < n; i++) {
			int ans, up, down;
			set<int>::iterator it = vis.lower_bound(s[i].power);

			up = *it;

			if (it != vis.begin())
				it--;

			down = *it;

			if (abs(down - s[i].power) <= abs(up - s[i].power))
				ans = down;
			else
				ans = up;

			printf("%d %d\n", s[i].id, v[ans]);
			vis.insert(s[i].power);
		}
	}
	return 0;
}
