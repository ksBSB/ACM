#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100005;

struct Stack {
	int n, s[maxn];
	void init () { n = 0; }
	int find (int x) { return upper_bound(s, s + n, x) - s; }
	void modify(int pos, int val) { s[pos] = val; n = max(n, pos+1); }
}in, de;

int N, A[maxn];

int solve () {
	in.init();
	de.init();
	int ret = 0;
	for (int i = N; i; i--) {
		int l = in.find(A[i]);
		in.modify(l, A[i]);
		int r = de.find(-(A[i]+1));
		int tmp = de.find(-A[i]);
		de.modify(tmp, -A[i]);
		ret = max(ret, l + r);
	}
	return ret + 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		printf("%d\n", solve());
	}
	return 0;
}
