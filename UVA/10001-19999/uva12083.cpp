#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 505;

int N, L[maxn];
bool S[maxn], T[maxn];
vector<int> G[maxn];

int age[maxn], gender[maxn], music[maxn], sport[maxn], idP, idQ;
map<string, int> P, Q;

bool match(int u) {
	S[u] = true;
	for (int i = 0; i < G[u].size(); i++) {
		int j = G[u][i];
		if (!T[j]) {
			T[j] = true;
			if (!L[j] || match(L[j])) {
				L[j] = u;
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
		if (gender[i]) continue;
		memset(S, false, sizeof(S));
		memset(T, false, sizeof(T));
		if (match(i)) ret++;
	}
	return ret;
}

int getID(map<string,int>& M, int& n, char* s) {
	if (!M.count(s)) M[s] = n++;
	return M[s];
}

bool judge (int a, int b) {
	if (abs(age[a]-age[b]) > 40) return false;
	if (gender[a] == gender[b]) return false;
	if (music[a] != music[b]) return false;
	if (sport[a] == sport[b]) return false;
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		idP = idQ = 0;
		P.clear(); Q.clear();

		char s1[maxn], s2[maxn], s3[maxn];
		for (int i = 1; i <= N; i++) {
			scanf("%d%s%s%s", &age[i], s1, s2, s3);
			gender[i] = (s1[0] == 'M');
			music[i] = getID(P, idP, s2);
			sport[i] = getID(Q, idQ, s3);
		}

		for (int i = 1; i <= N; i++) {
			if (gender[i]) continue;
			G[i].clear();
			for (int j = 1; j <= N; j++) if (i != j) {
				if (judge(i, j))
					G[i].push_back(j);
			}
		}

		int t = KM();
		printf("%d\n", N - t);
	}
	return 0;
}
