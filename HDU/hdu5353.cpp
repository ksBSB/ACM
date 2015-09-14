#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int maxn = 1e5 + 5;

ll sum;
vector<pii> ans;
int N, M, A[maxn], B[maxn];

void init () {
	sum = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		sum += A[i];
	}
}

inline int cmp(int k) {
	if (k == M)
		return 0;
	return k > M ? 1 : -1;
}

bool judge (int mv) {
	ans.clear();
	memcpy(B, A, sizeof(A));
	for (int i = 0; i < N; i++) {
		if (B[i] < 0)
			return false;
		int v = (i + 1) % N;
		if (mv > 0)
			ans.push_back(make_pair(i, v));
		else if (mv < 0)
			ans.push_back(make_pair(v, i));
		B[i] -= mv;
		B[v] += mv;
		mv = cmp(B[v]);
	}

	for (int i = 0; i < N; i++)
		if (B[i] != M)
			return false;
	return true;
}

bool solve () {
	for (int i = -1; i <= 1; i++)
		if (judge(i))
			return true;
	/*
	if (A[0] == 0) {
		return judge(0);
	} else if (A[0] == 2) {
		return judge(1);
	} else if (A[0] == -2) {
		return judge(-1);
	} else if (A[0] == 1) {
		return judge(0) || judge(1);
	} else if (A[0] == -1) {
		return judge(0) || judge(-1);
	}
	*/
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		if (sum % N)
			printf("NO\n");
		else {
			M = sum / N;

			if (solve()) {
				printf("YES\n");
				printf("%lu\n", ans.size());
				for (int i = 0; i < ans.size(); i++)
					printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
			} else
				printf("NO\n");
		}
	}
	return 0;
}
