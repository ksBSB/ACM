#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)

const int N = 1005;
const int INF = 1 << 20;

int n, m, k, tmp, t[N];
int f[N][N], g[N][N], rec[N];
char name[N][N];

int find(char *ch) {
	for (int i = 0; i < tmp; i++) {
		if (strcmp(ch, name[i]) == 0) return i;
	}

	strcpy(name[tmp], ch);
	return tmp++;
}

void init() {

	tmp = 1;
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	memset(name, 0, sizeof(name));

	char ch[N], na[N];

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {

		scanf("%s", ch);
		int p = find(ch);
		g[0][p]++;
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {

		scanf("%s%s", na, ch);
		int p = find(ch);
		rec[i] = p;
	}

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {

		scanf("%s%s", ch, na);
		int p = find(ch), q= find(na);
		g[q][p] = INF;
	}
}

int solve() {
	queue<int> q;
	int ans = 0;

	for (int i = 0; i < m; i++)
		g[rec[i]][tmp]++;
	
	while (1) {

		int b = 0;
		memset(t, 0, sizeof(t));
		memset(rec, 0, sizeof(rec));

		q.push(b);
		t[b] = INF;

		while (!q.empty()) {

			b = q.front(), q.pop();

			for (int i = 1; i <= tmp; i++) {

				if (!t[i] && g[b][i] > f[b][i]) {

					int cur = min(g[b][i] - f[b][i], t[b]);
					if (cur > t[i]) {

						t[i] = cur;
						rec[i] = b;
						q.push(i);
					}
				}
			}
		}

		if (t[tmp] == 0) break;
		ans += t[tmp];
		for (int i = tmp; i; i = rec[i]) {
			f[rec[i]][i] += t[tmp];
			f[i][rec[i]] -= t[tmp];
		}
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {

		init();
		printf("%d\n", m - solve());

		if (cas) printf("\n");
	}
	return 0;
}
