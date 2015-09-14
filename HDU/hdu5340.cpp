#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 50005;

/********* mannachar *************/
int rad[maxn];
char str[maxn];

int manachar(char* tmpstr) {
	int len = strlen(tmpstr), mv = 0;
	str[mv++] = '$';
	for (int i = 0; i <= len; i++) {
		str[mv++] = '#';
		str[mv++] = tmpstr[i];
	}

	int ans = 0, mix = 0, idx = 0;
	for (int i = 1; i <= mv; i++) {
		if (mix > i)
			rad[i] = min(rad[2 * idx - i], mix - i);
		else
			rad[i] = 1;

		for ( ; str[i - rad[i]] == str[i + rad[i]]; rad[i]++) {
			if (mix < i + rad[i]) {
				mix = i + rad[i];
				idx = i;
			}
		}
		ans = max(ans, rad[i]);
	}
	return ans - 1;
}

/*********************************/

int N;
vector<int> L, R;
vector<pii> G;
char s[maxn];

bool solve () {
	N = strlen(s);
	//G.clear();
	L.clear();
	R.clear();

	for (int i = 0; i < N; i++) {
		int k = rad[i * 2 + 2] / 2 - 1;
		int l = i - k;
		int r = i + k;
		//G.push_back(make_pair(l + 1, r + 1));
		if (l == 0)
			L.push_back(r + 1);
		if (r == N - 1)
			R.push_back(l + 1);
	}
	for (int i = 1; i < N; i++) {
		int k = rad[i * 2 + 1] / 2;
		int l = i - k;
		int r = i + k - 1;
		if (l == 0)
			L.push_back(r + 1);
		if (r == N - 1)
			R.push_back(l + 1);
	}
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());

	for (int i = 0; i < L.size(); i++) {
		for (int j = R.size() - 1; j >= 0; j--) {
			if (L[i] + 1 >= R[j])
				break;
			
			int k = L[i] + R[j];
			int l = rad[k] - 1;
			if (l >= R[j] - L[i] - 1) {
	//			printf("%d %d %d\n", L[i], R[j], l);
				return true;
			}
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", s);
		manachar(s);
		printf("%s\n", solve() ? "Yes" : "No");
	}
	return 0;
}
