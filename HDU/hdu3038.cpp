#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;
const int N = 200005;
//const ll UFmod = 0x3f3f3f3f3f;

struct UFset {
	int root;
	int parent;
	ll value;
}U[N];

int UFfind(int x) {
	if (U[x].root == 0) {
		int tmp = U[x].parent;
		U[x].parent = UFfind(U[x].parent);
//		U[x].value = (U[x].value + U[tmp].value) % UFmod;
		U[x].value = U[x].value + U[tmp].value;
		return U[x].parent;
	} else
		return x;
}

void UFunion(int x, int y, int p, int q, ll type) {
	U[p].parent += U[q].parent;

	U[q].parent = p;
	U[q].root = 0;
//	U[q].value = (U[x].value + type + UFmod - U[y].value) % UFmod;
	U[q].value = (U[x].value + type - U[y].value);
}

void UFinit (int n) {
	for (int i = 0; i <= n; i++) {
		U[i].parent = 1;
		U[i].value = 0;
		U[i].root = 1;
	}
}

int n, m;

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		UFinit(n);
		int a, b, ans = 0;
		ll c;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			cin >> c;
			a--;
			int p = UFfind(a), q = UFfind(b);

			if (p == q) {
				if (U[a].value + c != U[b].value)
					ans++;
			} else {
				UFunion(a, b, p, q, c);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
