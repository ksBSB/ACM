#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 4000005;
const int maxl = 1005;

char type[maxn];
ll ans;
int sz, val[maxn];
int son[maxn], bro[maxn];

void init () {
	sz = 1;
	ans = 0;
	son[0] = bro[0] = val[0] = 0;
}

void insert (char* s) {
	int n = strlen(s);
	int u = 0;

	for (int i = 0; i <= n; i++) {
		int v = 0;
		for (int j = son[u]; j; j = bro[j]) {
			if (type[j] == s[i]) {
				v = j;
				ans += val[j] * 2;
			} else
				ans += val[j];
		}

		if (v == 0) {
			v = sz++;
			type[v] = s[i];
			val[v] = son[v] = 0;
			bro[v] = son[u];
			son[u] = v;
		}

		u = v;
		val[u]++;
	}
}

int main () {
	int cas = 1, n;
	char word[maxl];

	while (scanf("%d", &n) == 1 && n) {
		ans = 0;
		init();
		for (int i = 0; i < n; i++) {
			scanf("%s", word);
			insert(word);
		}

		printf("Case %d: %lld\n", cas++, ans);
	}
	return 0;
}
