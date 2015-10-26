#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;

char s[maxn];

int solve () {
	int n = strlen(s);
	vector<int> pos;

	for (int i = 0; i < n; i++) {
		if (s[i] == 'c')
			pos.push_back(i);
		else if (s[i] == 'f')
			continue;
		else
			return -1;
	}

	if (pos.size() == 0)
		return n % 2 + n / 2;
	pos.push_back(pos[0] + n);

	for (int i = 1; i < pos.size(); i++)
		if (pos[i] - pos[i-1] <= 2) return -1;
	return pos.size()-1;
}

int main () {
	int cas;
	scanf("%d%*c", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		gets(s);
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
