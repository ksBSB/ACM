#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 5005;

struct state {
	int ai, bi;
}s[maxn];
int N;

inline bool cmp (const state& a, const state& b) {
	if (a.ai != b.ai)
		return a.ai < b.ai;
	return a.bi < b.bi;
}

int main () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &s[i].ai, &s[i].bi);
	sort(s, s + N, cmp);

	int ans = s[0].bi;
	for (int i = 1; i < N; i++) {
		if (s[i].bi >= ans)
			ans = s[i].bi;
		else
			ans = s[i].ai;
	}
	printf("%d\n", ans);
	return 0;
}
