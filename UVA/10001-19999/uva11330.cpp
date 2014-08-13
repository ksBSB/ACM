#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e4+5;

int n, pos[maxn], v[maxn], arr[maxn];

int solve () {
	int ret = 0;
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++) {
		if (v[i])
			continue;

		ret++;

		int mv = i;
		while (v[mv] == 0) {
			v[mv] = 1;
			mv = arr[mv];
		}
	}
	return ret;
}

int main () {
	int cas, x;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < 2 * n; i++) {
			if (i&1)
				scanf("%d", &arr[i/2]);
			else {
				scanf("%d", &x);
				pos[x] = i/2;
			}
		}

		for (int i = 0; i < n; i++)
			arr[i] = pos[arr[i]];
		printf("%d\n", n - solve());
	}
	return 0;
}
