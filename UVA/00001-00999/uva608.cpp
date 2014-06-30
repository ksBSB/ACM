#include <stdio.h>
#include <string.h>

const int N = 105;
int v[N], l[3][N], r[3][N], s[3], cnt[3];

void init() {
	memset(s, 0, sizeof(s));
	memset(r, 0, sizeof(r));
	memset(l, 0, sizeof(l));

	for (int i = 0; i < 12; i++) v[i] = 1;

	char a[N], b[N], c[N];
	for (int i = 0; i < 3; i++) {
		scanf("%s%s%s", a, b, c);
		cnt[i] = strlen(a);

		for (int j = 0; j < cnt[i]; j++) l[i][j] = a[j] - 'A';
		for (int j = 0; j < cnt[i]; j++) r[i][j] = b[j] - 'A';

		if (c[0] == 'e') s[i] = 0;
		else if (c[0] == 'u') s[i] = 1;
		else if (c[0] == 'd') s[i] = -1;
	}
}

bool judge() {
	for (int i = 0; i < 3; i++) {
		int p = 0, q = 0;
		for (int j = 0; j < cnt[i]; j++) {
			p += v[l[i][j]]; q += v[r[i][j]];
		}
		if (s[i] == 0 && p != q) return false;
		if (s[i] > 0 && p <= q) return false;
		if (s[i] < 0 && p >= q) return false;
	}

	int x;
	for (x = 0; x < 12; x++) if(v[x] != 1) break;
	printf("%c is the counterfeit coin and it is %s.\n", 'A' + x, v[x] == 0 ? "light" : "heavy");
	return true;
}

void solve() {
	for (int i = 0; i < 12; i++) {
		v[i] = 2;
		if (judge()) return;
		v[i] = 0;
		if (judge()) return;
		v[i] = 1;
	}
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
