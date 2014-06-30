#include <stdio.h>
#include <string.h>
const int N = 105;

struct state {
    int l;
    int r; 
}tmp[N];
int n, dp[N][N], rec[N][N];

void Init() {
    memset(dp, 0, sizeof(dp));
    memset(rec, 0, sizeof(rec));

    for (int i = 0; i < n; i++)
	scanf("%d%d", &tmp[i].l, &tmp[i].r);
}

int solve(int a, int b) {
    if (dp[a][b])   return dp[a][b];
    if (a == b)	return 0;
    if (a + 1 == b) return dp[a][b] = tmp[a].l * tmp[a].r * tmp[b].r;

    int now, Max = 1 << 30;
    for (int i = a; i < b; i++) {
	now = solve(a, i) + solve(i + 1, b) + tmp[a].l * tmp[i].r * tmp[b].r;
	if (now < Max) {
	    Max = now;
	    rec[a][b] = i;
	}
    }
    dp[a][b] = Max;
    return Max;
}

void print(int a, int b) {
    if (a == b)
	printf("A%d", a + 1);
    else if (a + 1 == b)
	printf("(A%d x A%d)", a + 1, b + 1);
    else {
	printf("(");
	print(a, rec[a][b]);
	printf(" x ");
	print(rec[a][b] + 1, b);
	printf(")");
    }
}

int main() {
    int cas = 1;
    while (scanf("%d", &n), n) {
	Init();
	solve(0, n - 1);
	printf("Case %d: ", cas++);
	print(0, n - 1);
	printf("\n");
    }
    return 0;
}
