#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 30005;

int N, M, arr[maxn], v[maxn];

void solve () {
	priority_queue<int> a;
	priority_queue<int, vector<int>, greater<int> > b;

	for (int i = 1; i <= N; i++) {
		a.push(arr[i]);
		b.push(a.top());
		a.pop();

		while (v[i]--) {
			printf("%d\n", b.top());
			a.push(b.top());
			b.pop();
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int x;
		memset(v, 0, sizeof(v));
		scanf("%d%d", &N, &M);

		for (int i = 1; i <= N; i++)
			scanf("%d", &arr[i]);
		for (int i = 0; i < M; i++) {
			scanf("%d", &x);
			v[x]++;
		}

		solve();

		if (cas)
			printf("\n");
	}
	return 0;
}
