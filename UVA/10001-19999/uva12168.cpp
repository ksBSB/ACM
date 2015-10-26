#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 505;
typedef pair<string,string> pii;

int N, M, K, L[maxn];
bool T[maxn];
vector<int> G[maxn];
vector<pii> C, D;

bool match(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!T[v]) {
			T[v] = true;
			if (!L[v] || match(L[v])) {
				L[v] = u;
				return true;
			}
		}
	}
	return false;
}

int KM () {
	int ret = 0;
	memset(L, 0, sizeof(L));
	for (int i = 1; i <= N; i++) {
		memset(T, false, sizeof(T));
		if (match(i))
			ret++;
	}
	return ret;
}

void init () {
	C.clear();
	D.clear();

	scanf("%d%d%d", &N, &M, &K);
	char s1[10], s2[10];
	for (int i = 1; i <= K; i++) {
		scanf("%s%s", s1, s2);
		if (s1[0] == 'C')
			C.push_back(make_pair(s1, s2));
		else
			D.push_back(make_pair(s1, s2));
	}
	N = C.size();
	M = D.size();
	for (int i = 0; i < N; i++) {
		G[i+1].clear();
		for (int j = 0; j < M; j++) 
			if (C[i].first == D[j].second || C[i].second == D[j].first)
				G[i+1].push_back(j+1);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		int n = KM();
		printf("%d\n", K - n);
	}
	return 0;
}
