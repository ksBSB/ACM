#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int N, P;
vector<int> pos;
char s[maxn];

int solve () {
	int ret = 0, n = N / 2;;
	for (int i = 0; i < n; i++) {
		int tmp = abs(s[i] - s[N-i-1]);
		tmp = min(tmp, 26 - tmp);
		ret += tmp;
		if (tmp)
			pos.push_back(abs(i+1-P) < abs(N-i-P) ? i+1 : N-i);
	}
	n = pos.size();

	if (n == 0)
		return ret;
	sort(pos.begin(), pos.end());
	return ret + pos[n-1] - pos[0] + min(abs(pos[n-1]-P), abs(pos[0]-P));
}

int main () {
	scanf("%d%d%s", &N, &P, s);
	printf("%d\n", solve());
	return 0;
}
