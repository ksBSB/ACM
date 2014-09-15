#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N, H;

void solve (int l, int r, int h) {
	if (l > r)
		return;

	int mid = max(r - (1<<h) + 1, l);
	printf(" %d", mid);
	solve(l, mid - 1, h - 1);
	solve(mid + 1, r, h - 1);
}

int main () {
	int cas = 0;
	while (scanf("%d%d", &N, &H) == 2 && N + H) {
		printf("Case %d:", ++cas);
		if (N > (1<<H) - 1)
			printf(" Impossible.");
		else
			solve(1, N, H - 1);
		printf("\n");
	}
	return 0;
}
