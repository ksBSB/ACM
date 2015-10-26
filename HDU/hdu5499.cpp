#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int maxm = 50;
typedef pair<double,int> pii;

int N, M, S[maxn];
double R1[maxn], R2[maxn];
char name[maxn][maxm];
vector<pii> G1, G2, G;

void init () {
	G1.clear();
	G2.clear();
	scanf("%d%d", &N, &M);

	char sex[maxm];
	double MR1 = 0, MR2 = 0;
	for (int i = 0; i < N; i++) {
		scanf("%s%s%lf%lf", name[i], sex, &R1[i], &R2[i]);
		S[i] = sex[0] == 'm' ? 0 : 1;
		MR1 = max(MR1, R1[i]);
		MR2 = max(MR2, R2[i]);
	}

	for (int i = 0; i < N; i++) {
		double x = 0.3 * R1[i] * 300 / MR1 + 0.7 * R2[i] * 300 / MR2;
		if (S[i] == 0) G1.push_back(make_pair(x, i));
		else G2.push_back(make_pair(x, i));
	}
}

void solve () {
	G.clear();
	sort(G1.begin(), G1.end());
	sort(G2.begin(), G2.end());
	int p = G1.size()-1, q = G2.size()-1;

	if (G2.size() && M) {
		G.push_back(G2[q--]);
		M--;
	}

	while (M && (p >= 0 || q >= 0)) {
		if (q < 0 || (p >= 0 && G1[p].first > G2[q].first))
			G.push_back(G1[p--]);
		else
			G.push_back(G2[q--]);
		M--;
	}

	printf("The member list of Shandong team is as follows:\n");
	sort(G.begin(), G.end());
	for (int i = G.size()-1; i >= 0; i--)
		printf("%s\n", name[G[i].second]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
