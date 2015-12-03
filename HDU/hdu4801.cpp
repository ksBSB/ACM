#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 24;
int rot[6][maxn] = {{6, 1, 12, 3, 5, 11, 16, 7, 8, 9, 4, 10, 18, 13, 14, 15, 20, 17, 22, 19, 0, 21, 2, 23},
	{0, 1, 8, 14, 4, 3, 7, 13, 17, 9, 10, 2, 6, 12, 16, 15, 5, 11, 18, 19 ,20, 21, 22, 23},
	{2, 0, 3, 1, 6, 7, 8, 9, 23, 22, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 5, 4}};

int N, ans, C[maxn], T[maxn];

void rotate(int* a, int u) {
	for (int i = 0; i < maxn; i++)
		T[rot[u][i]] = a[i];
	memcpy(a, T, sizeof(T));
}

void dfs (int d) {

	int ret = 0, tmp[maxn];
	memcpy(tmp, C, sizeof(C));

	if (C[0] == C[1] && C[0] == C[2] && C[0] == C[3]) ret++;
	if (C[4] == C[5] && C[4] == C[10] && C[4] == C[11]) ret++;
	if (C[6] == C[7] && C[6] == C[12] && C[6] == C[13]) ret++;
	if (C[8] == C[9] && C[8] == C[14] && C[8] == C[15]) ret++;
	if (C[16] == C[17] && C[16] == C[18] && C[16] == C[19]) ret++;
	if (C[20] == C[21] && C[20] == C[22] && C[20] == C[23]) ret++;

	ans = max(ans, ret);

	if (d >= N) return;

	for (int i = 0; i < 6; i++) {
		memcpy(C, tmp, sizeof(tmp));
		rotate(C, i);
		dfs(d+1);
	}
}

int main () {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < maxn; j++)
			rot[i+3][rot[i][j]] = j;
	}

	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < maxn; i++) scanf("%d", &C[i]);
		ans = 0;
		dfs(0);
		printf("%d\n", ans);
	}
	return 0;
}
