#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e5;
bool v[maxn*2+5];
int N, M, f[maxn*2+5];

void init () {
	int a;
	scanf("%d%d", &N, &M);
	memset(v, 0, sizeof(v));

	for (int i = 0; i < N; i++) {
		scanf("%d", &a);
		v[a] = true;
	}

	int tmp = maxn * 2 + 1;
	for (int i = maxn * 2; i >= 0; i--) {
		if (v[i] == false)
			tmp = i;
		f[i] = tmp;
	}
}

int main () {
	int cas, a; 
	scanf("%d", &cas);
	while (cas--) {
		init();
		for (int i = 0; i < M; i++) {
			scanf("%d", &a);
			printf("%d\n", f[a]);
		}
	}
	return 0;
}
