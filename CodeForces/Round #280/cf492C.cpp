#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

struct Exams {
	int a, b;
}ex[maxn];

int N, R, avg;
ll S;

inline bool cmp (const Exams& A, const Exams& B) {
	return A.b < B.b;
}

void init () {
	S = 0;
	scanf("%d%d%d", &N, &R, &avg);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &ex[i].a, &ex[i].b);
		S += ex[i].a;
	}
	sort(ex, ex + N, cmp);
}

int main () {
	init();

	ll ans = 0, T = 1LL * N * avg;
	for (int i = 0; i < N; i++) {
		if (S >= T)
			break;
		ll add = min((ll)R - ex[i].a, T - S);
		ans += add * ex[i].b;
		S += add;
	}
	printf("%lld\n", ans);
	return 0;
}
