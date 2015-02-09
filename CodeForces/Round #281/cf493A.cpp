#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int inf = 0x3f3f3f3f;

int N, C[2][maxn];

int main () {
	char name[2][30], team[30], card[30];
	scanf("%s%s", name[0], name[1]);

	scanf("%d", &N);
	int t, num, s, f;
	for (int i = 0; i < N; i++) {
		scanf("%d%s%d%s", &t, team, &num, card);
		s = (team[0] == 'h' ? 0 : 1);
		f = (card[0] == 'y' ? 1 : 2);
		C[s][num] += f;

		if (C[s][num] >= 2) {
			printf("%s %d %d\n", name[s], num, t);
			C[s][num] = -inf;
		}
	}
	return 0;
}
