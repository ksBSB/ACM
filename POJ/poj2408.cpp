#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int maxn = 30005;
const int maxm = 30;
const int X = 30;
typedef unsigned long long ll;
typedef pair<ll,int> pii;

int N, M, E;
vector<pii> vec, grop;
vector<int> g[maxn];
char word[maxn][maxm], st[maxn][maxm];

inline ll Hash(char* s) {
	int len = strlen(s), c[maxm];
	memset(c, 0, sizeof(c));

	for (int i = 0; i < len; i++)
		c[s[i]-'a']++;

	ll ret = 0;
	for (int i = 0; i < 26; i++)
		ret = ret * X + c[i];
	return ret;
}

inline bool cmp (const pii& a, const pii& b) {
	if (a.second == b.second)
		return strcmp(st[a.first], st[b.first]) < 0;
	return a.second > b.second;
}

inline bool sort_by(const int& a, const int& b) {
	return strcmp(word[a], word[b]) < 0;
}

int main () {
	N = M = E = 0;
	vec.clear();
	grop.clear();

	while (scanf("%s", word[N]) == 1) {
		ll key = Hash(word[N]);
		vec.push_back(make_pair(key, N));
		N++;
	}
	sort(vec.begin(), vec.end());

	int cnt = 0;
	ll pre = -1;

	for (int i = 0; i < vec.size(); i++) {
		int idx = vec[i].second;
		if (vec[i].first != pre) {
			if (cnt)
				grop.push_back(make_pair(M++, cnt));
			cnt = 0;
			g[M].clear();
			pre = vec[i].first;
			strcpy(st[M], word[idx]);
		}

		cnt++;
		g[M].push_back(idx);
		if (strcmp(word[idx], st[M]) < 0)
			strcpy(st[M], word[idx]);
	}

	if (cnt)
		grop.push_back(make_pair(M++, cnt));
	sort(grop.begin(), grop.end(), cmp);

	for (int i = 0; i < min(5, (int)grop.size()); i++) {
		printf("Group of size %d: ", grop[i].second);
		int x = grop[i].first;
		sort(g[x].begin(), g[x].end(), sort_by);
		for (int j = 0; j < g[x].size(); j++) {
			if (j == 0 || strcmp(word[g[x][j-1]], word[g[x][j]]))
				printf("%s ", word[g[x][j]]);
		}
		printf(".\n");
	}
	return 0;
}
