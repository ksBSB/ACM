#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, pref[maxn][maxn], order[maxn][maxn], jump[maxn];
int future_husband[maxn], future_wife[maxn];
queue<int> Q;

void engage (int man, int woman) {
	int m = future_husband[woman];
	if (m) {
		future_wife[m] = 0;
		Q.push(m);
	}
	future_wife[man] = woman;
	future_husband[woman] = man;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) scanf("%d", &pref[i][j]);
			jump[i] = 1;
			future_wife[i] = 0;
			Q.push(i);
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				int x;
				scanf("%d", &x);
				order[i][x] = j;
			}
			future_husband[i] = 0;
		}

		while (!Q.empty()) {
			int man = Q.front();
			Q.pop();
			int woman = pref[man][jump[man]++];

			if (!future_husband[woman]) engage(man, woman);
			else if (order[woman][man] < order[woman][future_husband[woman]])
				engage(man, woman);
			else
				Q.push(man);
		}

		for (int i = 1; i <= N; i++)
			printf("%d\n", future_wife[i]);
		if (cas) printf("\n");
			
	}
	return 0;
}
