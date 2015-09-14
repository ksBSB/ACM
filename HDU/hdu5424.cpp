#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;
typedef pair<int,int> pii;

int N, C[maxn], F[maxn], si[5];
vector<pii> S;

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); } 

bool link (int u, int v) {
	if (find(u) != find(v)) {
		F[find(u)] = find(v);
		return true;
	}
	return false;
}

void init () {
	S.clear();
	memset(C, 0, sizeof(C));

	int u, v;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &u, &v);
		if (u == v) continue;
		S.push_back(make_pair(u, v));
	}

	for (int i = 0; i < S.size(); i++) {
		C[S[i].first]++;
		C[S[i].second]++;
	}
}

bool del (int u, int v, int& c1, int& c3) {
	c1 = c3 = 0;
	if (C[u] == 1 || C[v] == 1) return false;

	if (C[u] == 2) c1++;
	else c3++;
	if (C[v] == 2) c1++;
	else c3++;
	return true;
}

bool justify (int idx) {
	int n = N;
	for (int i = 1; i <= N; i++) F[i] = i;

	for (int i = 0; i < S.size(); i++) {
		if (idx == i) continue;
		if (link(S[i].first, S[i].second)) n--;
	}
	return n == 1;
}

bool judge () {
	if (N == 1) return true;

	memset(si, 0, sizeof(si));
	for (int i = 1; i <= N; i++) {
		if (C[i] > 3) return false;
		si[C[i]]++;
	}

	if (si[0] || si[3] > 2 || si[1] > 2) return false;

	if (si[3] == 0 && si[1] == 2 && justify(-1)) return true;

	int c1, c3;
	for (int i = 0; i < S.size(); i++) {
		if (del(S[i].first, S[i].second, c1, c3)) {
			if (si[3] == c3 && c1 + si[1] == 2 && justify(i)) return true;
		}
	}
	return false;
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
