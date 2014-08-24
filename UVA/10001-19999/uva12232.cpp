#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 20005;
const int maxm = 105;

bool flag;
int N, Q, f[maxn], d[maxn];

int getfar (int x) {

	if (x == f[x])
		return x;

	int tmp = f[x];
	f[x] = getfar(f[x]);
	d[x] ^= d[tmp];
	return f[x];
}

void query () {
	int n, ret = 0, num[maxm], vis[maxm];
	memset(vis, 0, sizeof(vis));

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
		num[i]++;
	}

	if (flag)
		return;

	for (int i = 0; i < n; i++) {

		int root = getfar(num[i]), cnt = 1;
		if (root == 0 || vis[i])
			continue;

		for (int j = i+1; j < n; j++) {
			if (getfar(num[j]) == root) {
				cnt++;
				vis[j] = 1;
			}
		}

		if (cnt&1) {
			printf("I don't know.\n");
			return ;
		}
	}

	for (int i = 0; i < n; i++)
		ret ^= d[num[i]];
	printf("%d\n", ret);
}

bool link () {
	char s[maxm];
	gets(s);

	int u, v, k;
	int type = sscanf(s, "%d%d%d", &u, &v, &k);
	u++;

	if (type == 2) {
		k = v;
		v = 0;
	} else
		v++;

	int p = getfar(u);
	int q = getfar(v);

	if (p == 0)
		swap(p, q);

	if (p != q) {
		f[p] = q;
		d[p] = d[u]^d[v]^k;
	} else
		return (d[u]^d[v]) != k;
	return false;
}

int main () {
	int cas = 1;
	while (~scanf("%d%d", &N, &Q) && N) {

		printf("Case %d:\n", cas++);

		flag = false;
		memset(d, 0, sizeof(d));
		for (int i = 0; i <= N; i++)
			f[i] = i;

		int ti = 0, u, v;
		char s[maxm];
		for (int i = 0; i < Q; i++) {
			scanf("%s", s);

			if (s[0] == 'I') {
				ti++;
				if (link()) {
					flag = true;
					printf("The first %d facts are conflicting.\n", ti);
				}
			} else if (s[0] == 'Q')
				query();
		}
		printf("\n");
	}
	return 0;
}
