#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef multiset<int>::iterator iter;

int N, M, K;
multiset<int> G;
vector<int> S;

void init () {
	G.clear();
	scanf("%d%d%d", &N, &M, &K);

	int x;
	for (int i = 0; i < N; i++) {
		scanf("%d", &x);
		if (x == 0) continue;
		G.insert(x);
	}
}

ll solve () {
	S.clear();
	while (!G.empty()) {
		iter it = G.end(); it--;
		int u = *it;
		G.erase(it);

		it = G.upper_bound(K-u);
		if (it == G.begin()) continue;

		it--;
		int v = *it;
		G.erase(it);
		S.push_back(u * v);
	}

	ll ret = 0;
	sort(S.begin(), S.end());
	int n = S.size();
	for (int i = 1; i <= M && i <= n; i++) {
		ret += S[n-i];
	}

	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
