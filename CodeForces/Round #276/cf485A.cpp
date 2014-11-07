#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int a, m, v[maxn];

bool judge () {
	while (v[a] == 0) {
		v[a] = 1;
		a = a * 2 % m;
		if (a == 0)
			return true;
	}
	return false;
}

int main () {
	scanf("%d%d", &a, &m);
	printf("%s\n", judge() ? "Yes" : "No");
	return 0;
}
