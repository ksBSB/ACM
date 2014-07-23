#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef __int64 ll;
const int maxt = 1440;
const int maxd = 100;

int N, M;
int mach[maxd+10][maxt+10], task[maxd+10][maxt+10];

void init () {
	int a, b;
	memset(mach, 0, sizeof(mach));
	memset(task, 0, sizeof(task));

	for (int i = 0; i < N; i++) {
		scanf("%d%d", &a, &b);
		mach[b][a]++;
	}

	/*
	for (int i = maxd; i >= 0; i--)
		for (int j = maxt; j >= 0; j--)
			mach[i][j] = mach[i][j] + mach[i+1][j] + mach[i][j+1] - mach[i+1][j+1];
			*/

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);
		task[b][a]++;
	}
}

void solve () {
	ll ans = 0;
	int cnt = 0;

	for (int j = maxt; j >= 0; j--) {
		int tmp = 0;
		for (int i = maxd; i >= 0; i--) {

			mach[i][j] += mach[i][j+1];
			tmp += mach[i][j];

			int k = min(tmp, task[i][j]);
			ans += (ll)k * (2LL * i + 500LL * j);
			tmp -= k;
			cnt += k;

			for (int x = i; x <= maxd; x++) {
				int p = min(mach[x][j], k);
				k -= p;
				mach[x][j] -= p;

				if (k == 0)
					break;
			}
		}
	}
	printf("%d %I64d\n", cnt, ans);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		solve();
	}
	return 0;
}
