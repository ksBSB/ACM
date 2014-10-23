#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100000;

int N, c[maxn + 5];

int main () {
	while (scanf("%d", &N) == 1 && N) {
		int l, r;
		memset(c, 0, sizeof(c));

		for (int i = 0; i < N; i++) {
			scanf("%d%d", &l, &r);
			c[l]++; c[r+1]--;
		}

		int mv = 0;
		for (int i = 1; i <= N; i++) {
			mv += c[i];
			printf("%d%c", mv, i == N ? '\n' : ' ');
		}
	}
	return 0;
}
