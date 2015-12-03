#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 2 * 1e5 + 5;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> pii;

vector<pii> ans;
int N, X, L[maxn], R[maxn], pl[maxn], pr[maxn];

void init () {
	for (int i = 0; i < maxn; i++)
		pl[i] = pr[i] = inf;

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		L[i] = L[i-1];
		R[i] = R[i-1];
		scanf("%d", &X);
		if (X == 1)
			L[i]++;
		else
			R[i]++;
	}

	for (int i = 0; i <= N; i++) {
		pl[L[i]] = min(pl[L[i]], i);
		pr[R[i]] = min(pr[R[i]], i);
	}
}

void solve (int t) {
	int sa = 0, sb = 0;
	int pa = t, pb = t;
	int tmp = min(pl[t], pr[t]);

	while (true) {
		if (pl[pa] < pr[pb])
			sa++;
		else if (pl[pa] > pr[pb])
			sb++;
		int tmp = min(pl[pa], pr[pb]);
		if (tmp == N) {
			if (X == 1 && sa > sb)
				ans.push_back(make_pair(sa, t));
			else if (X == 2 && sa < sb)
				ans.push_back(make_pair(sb, t));
			return;
		} else if (tmp > N)
			return;
		pa = L[tmp] + t;
		pb = R[tmp] + t;
	}
}

int main () {
	init();
	for (int i = 1; i <= N; i++)
		solve(i);

	sort(ans.begin(), ans.end());
	printf("%lu\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
