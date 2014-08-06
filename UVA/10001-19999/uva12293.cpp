#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

bool judge (int n) {
	for (int i = 1; i < 32; i++)
		if (n == (1<<i) - 1)
			return false;
	return true;
}

int main () {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%s\n", judge(n) ? "Alice" : "Bob");
	}
	return 0;
}
