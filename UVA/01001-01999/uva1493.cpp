#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxr = 205;
const int maxc = 50005;

int N, M, Q, cnt[15];
int f[maxr][maxc];

struct Order {
	int sign, star, end;
	int x, y, r, w, c;
	void set (int sign, int x, int y, int c, int r, int w = 0) {
		this->sign = sign;
		this->x = x;
		this->y = y;
		this->c = c;
		this->r = r;
		this->w = w;
		del_star();
	}

	void del_star () {
		if (sign < 2) {
			star = max(x - r, 0);
			end = min(x + r, N - 1);
		} else if (sign == 2) {
			r = (r + 1) / 2 - 1;
			star = x;
			end = min(x + r, N-1);
		}
	}

}op[maxc];


int getfar (int* far, int x) {
	return x == far[x] ? x : far[x] = getfar(far, far[x]);
}

int style (char ch) {
	if (ch == 'C')
		return 0;
	else if (ch == 'D')
		return 1;
	else if (ch == 'T')
		return 2;
	else
		return 3;
}

void init () {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i <= M; i++) {
		for (int j = 0; j < N; j++)
			f[j][i] = i;
	}

	char s[20];
	int x, y, r, c, w;
	for (int i = 1; i <= Q; i++) {
		scanf("%s", s);
		if (s[0] != 'R') {
			scanf("%d%d%d%d", &x, &y, &r, &c);
			op[i].set(style(s[0]), x, y, c, r);
		} else {
			scanf("%d%d%d%d%d", &x, &y, &r, &w, &c);
			op[i].set(style(s[0]), x, y, c, r, w);
		}
	}
}

inline int get_R (int r, int x, int i, int sign) {
	if (sign == 0)
		return (int)sqrt(1.0 * r * r - 1.0 * (x - i) * (x - i));
	else if (sign == 1)
		return r - abs(x - i);
	else if (sign == 2)
		return r - (i - x);
	return 0;
}

int count (int x, int y, int r, int star, int end, int sign) {
	int ret = 0;
	for (int i = star; i <= end; i++) {
		int R = get_R(r, x, i, sign);

		int mv = max(y - R, 0);
		while (mv = getfar(f[i], mv), abs(mv - y) <= R && mv < M) {
			ret++;
			f[i][mv] = mv+1;
		}
	}
	return ret;
}

int count_rec (int x, int y, int r, int l) {
	int ret = 0;
	for (int i = x; i <= x + r - 1 && i < N; i++) {
		int mv = y;
		while (mv = getfar(f[i], mv), abs(mv - y) < l && mv < M) {
			ret++;
			f[i][mv] = mv+1;
		}
	}
	return ret;
}

void solve () {

	for (int i = Q; i; i--) {
		int& col = cnt[op[i].c];
		if (op[i].sign == 3)
			col += count_rec(op[i].x, op[i].y, op[i].r, op[i].w);
		else
			col += count(op[i].x, op[i].y, op[i].r, op[i].star, op[i].end, op[i].sign);
	}

	for (int i = 1; i <= 9; i++)
		printf("%d%c", cnt[i], i == 9 ? '\n' : ' ');
}

int main () {
	while (scanf("%d%d%d", &N, &M, &Q) == 3) {
		init();
		solve();
	}
	return 0;
}
