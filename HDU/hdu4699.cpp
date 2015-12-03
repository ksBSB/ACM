#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;

struct Stack {
	int n, s[maxn];
	void init() { n = 0; }
	bool empty() { return n == 0; }
	void push(int x) { s[n++] = x; }
	void pop() { n--; }
	int top() { return s[n-1]; }
	int get(int k) { return s[k-1]; }
}L, R;

int Q, S[maxn];
char order[20];

int main () {
	while (scanf("%d", &Q) == 1) {
		L.init(), R.init();
		int mv = 0, sum = 0, x;
		while (Q--) {
			scanf("%s", order);
			if (order[0] == 'I') {
				scanf("%d", &S[mv]);
				sum += S[mv++];
				if (L.empty()) L.push(sum);
				else L.push(max(sum, L.top()));
			} else if (order[0] == 'D' && !L.empty()) {
				sum -= S[--mv];
				L.pop();
			} else if (order[0] == 'L' && !L.empty()) {
				R.push(S[--mv]);
				sum -= S[mv];
				L.pop();
			} else if (order[0] == 'R' && !R.empty()) {
				S[mv] = R.top();
				R.pop();
				sum += S[mv++];
				if (L.empty()) L.push(sum);
				else L.push(max(sum, L.top()));
			} else if (order[0] == 'Q') {
				scanf("%d", &x);
				printf("%d\n", L.get(x));
			}
		}
	}
	return 0;
}
