#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef pair<string, int> pii;
const int maxn = 1e5+5;

int Rank[maxn];
int dp[maxn][20];
vector<pii> g;
vector<int> height;

void rmq_init(const vector<int>& A) {
	int n = A.size();
	for (int i = 0; i < n; i++)
		dp[i][0] = A[i];

	for (int j = 1; (1<<j) <= n; j++) {
		for (int i = 0; i + (1<<j) - 1 < n; i++)
			dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
	}
}

int rmq_query (int l, int r) {

	if (l == r)
		return g[l].first.length();

	if (l > r)
		swap(l, r);

	l++;

	int k = 0;
	while ((1<<(k+1)) <= r - l + 1)
		k++;
	return min(dp[l][k], dp[r - (1<<k) + 1][k]);
}

void solve () {
	sort(g.begin(), g.end());

	for (int i = 0; i < g.size(); i++)
		Rank[g[i].second] = i;

	height.clear();
	height.push_back(0);
	for (int i = 1; i < g.size(); i++) {
		int n = min(g[i].first.length(), g[i-1].first.length());;
		int j;
		for (j = 0; j < n; j++)
			if (g[i].first[j] != g[i-1].first[j])
				break;
		height.push_back(j);
	}
	rmq_init(height);
}

int main () {
	int cas, n, l, r;
	string s;
	cin >> cas;
	for (int kcas = 1; kcas <= cas; kcas++) {
		cin >> n;
		g.clear();

		for (int i = 0; i < n; i++) {
			cin >> s;
			g.push_back(make_pair(s, i));
		}
		solve();

		cout << "Case " << kcas << ":" << endl;
		cin >> n;
		while (n--) {
			cin >> l >> r;
			cout << rmq_query(Rank[l-1], Rank[r-1]) << endl;
		}
	}
	return 0;
}
