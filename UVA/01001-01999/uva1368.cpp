#include <stdio.h>
#include <string.h>

const int N = 1005;
const int M = 105;

int n, m, cnt[M];
char dna[M][N];

void init() {
	scanf("%d%d", &m, &n);
	for (int i = 0; i < m; i++) scanf("%s", dna[i]);
}

void solve() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int Max = 0, id;
		memset(cnt, 0, sizeof(cnt));
		for (int j = 0; j < m; j++) {
			int tmp = dna[j][i] - 'A';
			cnt[tmp]++;
			if (cnt[tmp] > Max) {
				Max = cnt[tmp];
				id = tmp;
			} else if (cnt[tmp] == Max && tmp < id)
				id = tmp;
		}
		ans += m - Max;
		printf("%c", 'A' + id);
	}
	printf("\n%d\n", ans);
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
