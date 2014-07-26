#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	int x = min(n, m);
	printf("%s\n", x&1? "Akshat" : "Malvika");
	return 0;
}
