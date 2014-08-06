#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100;

int s[maxn+5][9];

int SG (int l, int x, int y) {
	int vis[maxn+5];
	memset(vis, 0, sizeof(vis));

	for (int i = 1; i <= l; i++) {

		if ((i != 1 || x != 1) && (i != l || y != 1)) {
			int X = s[i-1][x*3+1] ^ s[l-i][1*3+y];
			vis[X] = 1;
		}

		if ((i != 1 || x != 2) && (i != l || y != 2)) {
			int O = s[i-1][x*3+2] ^ s[l-i][2*3+y];
			vis[O] = 1;
		}
	}

	int mv = -1;
	while (vis[++mv]);
	return mv;
}

void init (int n) {
	memset(s[0], 0, sizeof(s[0]));

	for (int i = 0; i < 9; i++)
		s[1][i] = 1;
	s[1][1*3+2] = s[1][2*3+1] = 0;


	for (int i = 2; i <= n; i++) {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++)
				s[i][x*3+y] = SG(i, x, y);
		}
	}
}

char str[maxn+5];

bool judge () {
	int len = strlen(str+1);

	int l = 0, r = 0, cnt = 0, ans = 0, k = 0;
	for (int i = 1; i <= len; i++) {
		if (str[i] == '.')
			k++;
		else {
			r = (str[i] == 'X' ? 1 : 2);
			ans ^= s[k][l*3+r];
			cnt++;
			l = r;
			k = 0;
		}
	}

	ans ^= s[k][l*3];
	if (cnt&1)
		ans = (ans == 0 ? 1 : 0);
	return ans;
}

int main () {
	init(maxn);
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str+1);
		printf("%s\n", judge() ? "Possible." : "Impossible.");
	}
	return 0;
}
