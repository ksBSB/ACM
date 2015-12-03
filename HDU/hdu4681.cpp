#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1005;

int N, M, K, l[maxn][maxn], r[maxn][maxn];
char A[maxn], B[maxn], C[maxn];
vector<pii> L, R;

void init () {
	scanf("%s%s%s", A + 1, B + 1, C + 1);
	N = strlen(A + 1);
	M = strlen(B + 1);
	K = strlen(C + 1);

	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (A[i] == B[j]) l[i][j] = l[i-1][j-1] + 1;
			else l[i][j] = max(l[i-1][j], l[i][j-1]);
		}
	}
	for (int i = N; i; i--) {
		for (int j = M; j; j--) {
			if (A[i] == B[j]) r[i][j] = r[i+1][j+1] + 1;
			else r[i][j] = max(r[i+1][j], r[i][j+1]);
		}
	}

	L.clear(); R.clear();
	for (int i = 1; i <= N; i++) if (A[i] == C[1]) {
		int mv = i, k = 0;
		while (mv <= N) {
			if (A[mv] == C[k+1]) k++;
			if (k == K) {
				L.push_back(make_pair(i, mv));
				break;
			}
			mv++;
		}
	}

	for (int i = 1; i <= M; i++) if (B[i] == C[1]) {
		int mv = i, k = 0;
		while (mv <= M) {
			if (B[mv] == C[k+1]) k++;
			if (k == K) {
				R.push_back(make_pair(i, mv));
				break;
			}
			mv++;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		int ans = 0;
		for (int i = 0; i < L.size(); i++) {
			for (int j = 0; j < R.size(); j++)
				ans = max(ans, K + l[L[i].first-1][R[j].first-1] + r[L[i].second+1][R[j].second+1]);
		}
		printf("Case #%d: %d\n", kcas, ans);
	}
	return 0;
}
