#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 15;
const int maxs = 105;

vector<int> g[maxn];
char a[maxs], b[maxs];

void init () {

	int v[maxn];
	for (int i = 0; i < maxn; i++) {

		int tmp = i;
		memset(v, 0, sizeof (v));

		while (v[tmp] == 0) {
			v[tmp] = 1;
			g[i].push_back(tmp);
			tmp = tmp * i % 10;
		}
	}
}

int main () {
	init();
	while (scanf("%s%s", a, b) == 2 && ( strcmp(a,"0") || strcmp(b,"0")) ) {

		if (strcmp(b, "0") == 0) {
			printf("1\n");
			continue;
		}

		int u = a[strlen(a)-1] - '0';
		int len = strlen(b);

		int tmp = 1, m = g[u].size();
		for (int i = 0; i < len; i++)
			tmp = (tmp * 10 + (b[i] - '0')) % m;
		printf("%d\n", g[u][(tmp-1+m)%m]);
	}
	return 0;
}
