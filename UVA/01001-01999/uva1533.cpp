#include <stdio.h>
#include <string.h>

const int dir[15][6] = { 
	{-1, -1, -1, -1, 2, 3}, {-1, 1, -1, 3, 4, 5}, {1, -1, 2, -1, 5, 6},   
	{-1, 2, -1, 5, 7, 8}, {2, 3, 4, 6, 8, 9}, {3, -1, 5, -1, 9, 10},   
	{-1, 4, -1, 8, 11, 12}, {4, 5, 7, 9, 12, 13}, {5, 6, 8, 10, 13, 14},   
	{6, -1, 9, -1, 14, 15}, {-1, 7, -1, 12, -1, -1}, {7, 8, 11, 13, -1, -1},   
	{8, 9, 12, 14, -1, -1}, {9, 10, 13, 15, -1, -1}, {10, -1, 14, -1, -1, -1}  };
const int M = 20;
const int N = 70000;

struct state {
	int far;
	int val;
	int x, y, d;
}q[N];
int n, pTow[M], v[N];

bool judge(int u, int c, int tmp, state& now) {
	int s = c;
	bool flag = false;

	u -= pTow[c]; c = dir[c][tmp]-1;
	while (c > -1) {
		if ((u & pTow[c]) == 0) {
			if (!flag) return false;
			now.val = u + pTow[c];
			now.x = s, now.y = c; 
			return true;
		}
		u -= pTow[c];
		c = dir[c][tmp]-1; flag = true;
	}
	return false;
}

bool handle(state c, int l, int &r) {
	int u = c.val;
	state cur;
	for (int i = 0; i < 15; i++) {
		if ((u & pTow[i]) == 0) continue;

		for (int j = 0; j < 6; j++) {
			if (dir[i][j] == -1) continue;
			if (judge(u, i, j, cur) && !v[cur.val]) {
				cur.far = l; v[cur.val] = 1; cur.d = q[l].d+1;
				q[r++] = cur;
				if (cur.val == pTow[n-1]) return true;
			}
		}
	}
	return false;
}

void solve() {
	scanf("%d", &n);

	int start = (pTow[15] - 1) - pTow[n-1];
	int l = 0, r = 0;
	memset(v, 0, sizeof(v)); v[start] = 1;
	q[r].far = 0; q[r].val = start; q[r].d = 0; r++;

	while (l < r) {
		state u = q[l++];
		if(handle(u, l-1, r)) break;
	}

	printf("%d\n", q[r-1].d);
	int cnt = 0, p[M];
	for (int i = r-1; i; i = q[i].far) p[cnt++] = i;
	printf("%d %d", q[p[cnt-1]].x + 1, q[p[cnt-1]].y + 1);
   for (int i = cnt - 2; i >= 0; i--) printf(" %d %d", q[p[i]].x + 1, q[p[i]].y + 1);	
   printf("\n");
}


int main() {
	int cas; scanf("%d", &cas);
	pTow[0] = 1;
	for (int i = 1; i <= 16; i++) pTow[i] = pTow[i-1] * 2;

	while (cas--) {
		solve();
	}
	return 0;
}
