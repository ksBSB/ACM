#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10005;

int N, M, d[maxn][20];
char s[maxn];

void rmq_init() {
	N = strlen(s);
	for (int i = 0; i < N; i++)
		d[i][0] = s[i];
	for (int k = 1; (1<<k) <= N; k++) {
		for (int i = 0; i < N; i++)
			d[i][k] = min(d[i][k-1], d[i+(1<<(k-1))][k-1]);
	}
}

int rmq_query(int l, int r) {
	int k = 0;
	while ((1<<(k+1)) <= r - l + 1) k++;
	return min(d[l][k], d[r-(1<<k)+1][k]);
}

int main () {
	while (scanf("%s%d", s, &M) == 2) {
		rmq_init();
		M = N - M;

		int mv = 0;
		bool flag = true;

		for (int i = M; i; i--) {
			int c = rmq_query(mv, N - i);

			while (mv < N && s[mv] != c) mv++;
			mv++;

			if (c == '0' && flag)
				continue;

			flag = false;
			printf("%c", c);
		}

		if (flag)
			printf("0");
		printf("\n");
	}
	return 0;
}
