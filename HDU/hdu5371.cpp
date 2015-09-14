#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator iter;
const int maxn = 100005 * 2;

int N, A[maxn];
set<int> S;
vector<pii> V;

/********* mannachar *************/
int rad[maxn], str[maxn];

void manachar(int* tmpstr) {
	int len = N, mv = 0;
	str[mv++] = -2;
	for (int i = 1; i <= len; i++) {
		str[mv++] = -1;
		str[mv++] = tmpstr[i];
	}
	str[mv++] = -1;

	int ret = 0, mix = 0, idx = 0;
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

		if (str[i] == -1)
			V.push_back(make_pair(rad[i]-1, i/2));
	}
}

/*********************************/

void init () {
	V.clear();
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	manachar(A);
	sort(V.begin(), V.end());
}

int solve () {
	int ret = 0;
	S.clear();

	for (int i = V.size() - 1; i >= 0; i--) {
		int len = V[i].first;
		int idx = V[i].second;
		iter it = S.upper_bound(idx + len / 2);
		if (it != S.begin()) {
			it--;
			int iidx = *it;
			ret = max(ret, (iidx - idx) * 3);
		}

		it = S.lower_bound(idx - len / 2);
		if (it != S.end()) {
			int iidx = *it;
			ret = max(ret, (idx - iidx) * 3);
		}
		S.insert(idx);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init ();
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
