#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 25;
const int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
const int change[4] = {2, 3, 0, 1};

inline int idx(char ch) {
	if (ch == 'N')
		return 0;
	if (ch == 'W')
		return 1;
	if (ch == 'S')
		return 2;
	return 3;
}

struct rabbits {
	int d, x, y, s, t;
	void input (int x, int y) {
		this->x = x;
		this->y = y;

		char o[3];
		scanf("%s%d%d", o, &s, &t);
		d = idx(o[0]);
	}
	void turn() { d = (d + 1) % 4;}
	void move(int n) {
		for (int i = 0; i < s; i++) {
			int p = x + dir[d][0];
			int q = y + dir[d][1];

			if (p <= 0 || p > n || q <= 0 || q > n) {
				d = change[d];
				i--;
				continue;
			}
			x = p;
			y = q;
		}
	}
	bool operator == (const rabbits& a) {
		return x == a.x && y == a.y;
	}

}A, B;
int N, K;

int main () {
	while (scanf("%d", &N) == 1 && N) {
		A.input(1, 1);
		B.input(N, N);
		scanf("%d", &K);

		for (int i = 1; i <= K; i++) {
			A.move(N);
			B.move(N);

			if (A == B)
				swap(A.d, B.d);
			else {
				if (i % A.t == 0)
					A.turn();
				if (i % B.t == 0)
					B.turn();
			}
			/*
			   printf("%d %d!\n", A.x, A.y);
			   printf("%d %d!\n", B.x, B.y);
			   */
		}
		printf("%d %d\n", A.x, A.y);
		printf("%d %d\n", B.x, B.y);
	}
	return 0;
}
