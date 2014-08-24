#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1005;
int N, arr[maxn][maxn];

struct item {
	int s, pos;
	item (int s = 0, int pos = 0) {
		this->s = s;
		this->pos = pos;
	}

	bool operator < (const item& u) const {
		return s > u.s;
	}
};

void merge (int* A, int* B, int* C, int n) {
	priority_queue<item> pri_que;
	for (int i = 0; i < n; i++)
		pri_que.push(item(A[i] + B[0], 0));

	for (int i = 0; i < n; i++) {
		item u = pri_que.top();
		pri_que.pop();

		C[i] = u.s;
		if (u.pos + 1 < n)
			pri_que.push(item(u.s - B[u.pos] + B[u.pos+1], u.pos+1));
	}
}

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				scanf("%d", &arr[i][j]);
			sort(arr[i], arr[i] + N);
		}

		for (int  i = 1; i < N; i++)
			merge(arr[0], arr[i], arr[0], N);

		printf("%d", arr[0][0]);
		for (int i = 1; i < N; i++)
			printf(" %d", arr[0][i]);
		printf("\n");
	}
	return 0;
}
