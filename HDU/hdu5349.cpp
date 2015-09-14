#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

typedef set<int>::iterator iter;
set<int> S;

int main () {
	int n, k, x;
	while (scanf("%d", &n) == 1) {
		S.clear();
		while (n--) {
			scanf("%d", &k);
			if (k == 1) {
				scanf("%d", &x);
				S.insert(x);
			} else if (k == 2 && !S.empty())
				S.erase(S.begin());
			else if (k == 3) {
				if (S.empty())
					printf("0\n");
				else {
					iter it = S.end();
					it--;
					printf("%d\n", *it);
				}
			}
		}
	}
	return 0;
}
