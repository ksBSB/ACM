#include <stdio.h>
#include <string.h>

const int MAXN = 105;
const int N = 52;
const char value[][10] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
const char suit[][10] = { "Clubs", "Diamonds", "Hearts", "Spades" };

int n, dir[MAXN][MAXN], ans[MAXN];

void init() {
	scanf("%d", &n);
	for (int k = 1; k <= n; k++)
		for (int i = 1; i  <= N; i++)
			scanf("%d", &dir[k][i]);
	for (int i = 1; i <= N; i++)
		ans[i] = i;
}

void solve(int a[], int d[]) {
	int c[MAXN];
	for (int i = 1; i <= N; i++)
		c[i] = a[d[i]];

	for (int i = 1; i <= N; i++)
		a[i] = c[i];
}

int main () {
	int cas, num;
	char order[N];
	scanf("%d", &cas);
	while (cas--) {
		init();
		getchar();

		while (gets(order) && order[0] != '\0') {
			sscanf(order, "%d", &num);
			solve(ans, dir[num]);
		}

		for (int i = 1; i <= N; i++)
			printf("%s of %s\n", value[ans[i] % 13], suit[(ans[i] - 1) / 13]);
		if (cas) printf("\n");
	}
	return 0;
}
