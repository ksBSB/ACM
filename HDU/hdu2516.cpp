#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
int n;
ll k, fbi[50];

bool judge () {
	for (int i = 0; i < n; i++)
		if (fbi[i] == k)
			return false;
	return true;
}

int main () {
	fbi[0] = 2;
	fbi[1] = 3;
	for (n = 2; fbi[n-1] >= (1<<31); n++)
		fbi[n] = fbi[n-1] + fbi[n-2];
	while (scanf("%lld", &k) == 1 && k) {
		printf("%s\n", judge() ? "First win" : "Second win");
	}
	return 0;
}
