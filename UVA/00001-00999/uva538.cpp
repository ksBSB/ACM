#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M;
map<string, int> G;
int V[maxn], W;
char name[maxn][maxn], s[maxn], t[maxn];

int main () {
	int cas = 1;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		G.clear();
		memset(V, 0, sizeof(V));
		for (int i = 1; i <= N; i++) {
			scanf("%s", name[i]);
			G[name[i]] = i;
		}

		for (int i = 0; i < M; i++) {
			scanf("%s%s%d", s, t, &W);
			V[G[s]] -= W, V[G[t]] += W;
		}

		printf("Case #%d\n", cas++);
		for (int i = 1; i < N; i++) {
			if (V[i] < 0)
				printf("%s %s %d\n", name[N], name[i], -V[i]);
			else
				printf("%s %s %d\n", name[i], name[N], V[i]);
			V[N] -= V[i];
		}
		printf("\n");
	}
	return 0;
}
