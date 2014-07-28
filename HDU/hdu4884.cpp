#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, T, K, M, ans[maxn];
struct state {
	int t, id, s;
	int ans, flag;
}p[maxn];

void init () {
	scanf("%d%d%d%d", &N, &T, &K, &M);

	int hh, mm;
	for (int i = 0; i < M; i++) {
		scanf("%d:%d%d%d", &hh, &mm, &p[i].id, &p[i].s);
		p[i].t = hh * 60 + mm;
		p[i].flag = 0;
	}
}

void solve () {
	int tmp = 0;
	for (int i = 0; i < M; i++) {

		if (p[i].flag)
			continue;

		int k = (p[i].s + K - 1) / K;
		int mv = max(tmp, p[i].t) + (k - 1) * T;
		int have = k * K;

		for (int j = i; j < M; j++) {
			if (p[j].t > mv || have == 0)
				break;

			if (p[j].id == p[i].id) {
				int del = min(have, p[j].s);
				have -= del;
				p[j].s -= del;
				if (p[j].s == 0 && p[j].flag == 0) {
					p[j].ans = mv + T;
					p[j].flag = 1;
				}
			}
		}
		tmp = mv + T;
	}
	for (int i = 0; i < M; i++)
		printf("%02d:%02d\n", (p[i].ans / 60) % 24, p[i].ans % 60);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if (cas)
			printf("\n");
	}
	return 0;
}
