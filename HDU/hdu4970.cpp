#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;
typedef unsigned long long ll;

int N, M;
ll v[maxn];

void init () {
	int l, r, val;

	scanf("%d", &M);
	memset(v, 0, sizeof(v));
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &l, &r, &val);
		v[l] += val;
		v[r+1] -= val;
	}

	ll mv = 0;
	for (int i = 0; i <= N; i++) {
		mv += v[i];
		v[i] = mv;
	}

	for (int i = 1; i <= N; i++)
		v[i] += v[i-1];
}

int main () {

	while (scanf("%d", &N) == 1 && N) {
		init();

		scanf("%d", &M);

		int pos, ret = 0;
		ll HP;
		for (int i = 0; i < M; i++) {
			scanf("%I64d%d", &HP, &pos);
			if (HP > v[N] - v[pos-1])
				ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}
