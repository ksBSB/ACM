#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int N = 105;
typedef pair<int, int> pi;

char order[N];


void solve() {
	int c, cnt = 0, p = 0;
	deque<pi> que;

	while (true) {
		scanf("%s", order);

		if (strcmp(order, "C") == 0) {
			scanf("%s %d", order, &c);

			while ( !que.empty() ) {
				pi cur = que.back();
				if (cur.first >= c) break;
				que.pop_back();
			}
			que.push_back(make_pair(c, cnt) );
			cnt++;

		} else if (strcmp(order, "Q") == 0) {

			if (que.empty())
				printf("-1\n");		
			else {
				pi tmp = que.front();
				printf("%d\n", tmp.first);
			}

		} else if (strcmp(order, "G") == 0) {

			if ( !que.empty() ) {
				pi cur = que.front();
				if (cur.second == p)
					que.pop_front();
				p++;
			}

		} else if (strcmp(order, "END") == 0) {
			return;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		solve();
	}
	return 0;
}
