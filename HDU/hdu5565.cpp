#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e7 + 1;
const int mod = 1e9 + 7;
const int G = 78125;

int N, Q, S, T, A[maxn];
deque<int> L[maxn], R[maxn];

int mrand(int l, int r) {
	S = 1LL * S * G % mod;
	return l + S % (r-l+1);
}

void init () {
	scanf("%d%d%d", &N, &Q, &S);
	T = 0;
	int sum = mrand(Q, 10000000);
	for(int i = 1; i <= N; i++) {
		A[i] = mrand(0, sum/(N-i+1));
		sum -= A[i];
		T = max(T, A[i]);
	}
	int tmp = mrand(1, N);
	A[tmp] += sum;
	T = max(T, A[tmp]);

	for (int i = 0; i <= T; i++) {
		L[i].clear();
		R[i].clear();
	}
	for (int i = 1; i <= N; i++)
		L[A[i]].push_back(i);
}

int solve () {
	while (Q--) {
		if (L[T].empty() && R[T].empty()) T--;

		if (R[T].empty() || (!L[T].empty() && L[T].front() < R[T].front())) {
			R[T-1].push_back(L[T].front());
			L[T].pop_front();
		} else {
			R[T-1].push_back(R[T].front());
			R[T].pop_front();
		}
	}

	for (int i = 0; i < T; i++) {
		for (int j = 0; j < L[i].size(); j++) A[L[i][j]] = i;
		for (int j = 0; j < R[i].size(); j++) A[R[i][j]] = i;
	}

	int ans = 0;
	for (int i = 1; i <= N; i++)
		ans ^= (A[i] + i);
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
